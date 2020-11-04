// Copyright © 2020  Philip Lindh 
// All rights reserved

#pragma once

#include "TextureResource.h"
#include "MeshResource.h"
#include "MaterialResource.h"
#include "Transform.h"

#include <functional>

struct Line
{
	// The line coordinates
	int x1, y1; 
	int x2, y2;

	// Pre-calculation for dx & dy multiplied by 2
	int dx2, dy2;

	// The direction in which the line steps towards
	int stepX, stepY;

	// Used to determine where the line is at during computation
	int currentX, currentY;

	// The amount of which 'y' increased as of last incrementation, AKA "error"
	// Assumes error margin of '0' instead of 0.5 or 1
	int fraction;

	/// <summary>
	/// Constructs a line filling in the member-variables for future use/drawing
	/// </summary>
	/// <param name="start">The starting point of the line</param>
	/// <param name="end">Where the line will stop</param>
	Line(Vector4* start, Vector4* end)
	{
		x1 = static_cast<int>(start->X);
		y1 = static_cast<int>(start->Y);
		x2 = static_cast<int>(end->X);
		y2 = static_cast<int>(end->Y);

		currentX = x1; 
		currentY = y1;

		// determines a positive or negative direction 
		stepX = x2 - x1 < 0 ? -1 : 1;
		stepY = y2 - y1 < 0 ? -1 : 1;

		const int dx = abs(x2 - x1);
		const int dy = abs(y2 - y1);

		dx2 = dx << 1;
		dy2 = dy << 1;

		fraction = dy2 - dx;
	}
};

/// <summary>
/// Makes out what's being rendered in the SoftwareRenderer class
/// </summary>
class RenderableObject
{
public:
	std::shared_ptr<MeshResource> MeshRes;
	std::shared_ptr<MaterialResource> MaterialRes;
	std::shared_ptr<TextureResource> TextureRes;
	std::shared_ptr<Transform> TransformRes;

	RenderableObject(std::shared_ptr<MeshResource> mesh, std::shared_ptr<MaterialResource> material, std::shared_ptr<TextureResource> texture, std::shared_ptr<Transform> transform) :
		MeshRes(move(mesh)), MaterialRes(move(material)), TextureRes(move(texture)), TransformRes(move(transform)) { }
};

/// <summary>
/// Manages rendering computed at the CPU using oldschool techniques with modern appliances 
/// </summary>
class SoftwareRenderer
{
public:

	SoftwareRenderer();

	void Draw(Matrix4x4& view, Matrix4x4& projection);

	void SetVertexShader(const std::function<Vertex(Vertex & vertex, Matrix4x4 & model, Matrix4x4 & view, Matrix4x4 & projection)>& shader) { this->vertexShader = shader; };
	void SetPixelShader(const std::function<Vector3(Vertex & vertex, Texture & texture, Material & material)>& shader) { this->pixelShader = shader; };

	void AddRenderableObject(RenderableObject& object) { targets.emplace_back(std::move(object)); };

	PixelColor* GetPtr() const { return framebuffer; }

	int GetSize()   const { return size; }
	int GetWidth()  const { return width; }
	int GetHeight() const { return height; }

	~SoftwareRenderer() = default;

private:
	std::vector<RenderableObject> targets;

	PixelColor* framebuffer;
	float* depthbuffer;
	float farplane;
	float nearplane;
	PixelColor backgroundColor;

	float pixelWidth;
	float pixelHeight;

	int width;
	int height;
	int size;

	void SetPixel(int x, int y, Vector3& color) const;
	void ClearBuffers() const;
	
	// Inserts pixels into the buffer by iterating through P1 to P2
	void FillHorizontalLine(RenderableObject& target, Vector4(&points)[3], Vertex(&vertices)[3], int x1, int y, int x2) const;
	void FillOutline(RenderableObject& target, Vector4(&points)[3], Vertex(&vertices)[3], Line& line) const;

	void LineTest(RenderableObject& target, Vector4(&points)[3], Vertex(&vertices)[3], int x1, int y, int x2) const;
	void FillFlatBottomTriangle(RenderableObject& target, Vector4 (&points)[3], Vertex (&vertices)[3], const Vector4& v0, const Vector4& v1, const Vector4& v2) const;
	void FillFlatTopTriangle(RenderableObject& target, Vector4 (&points)[3], Vertex (&vertices)[3], const Vector4& v1, const Vector4& v2, const Vector4& v3) const;

	
	// Fills the triangle by drawing lines at the combination of the vertices 
	void FillTriangle(RenderableObject& target, Vector4(&points)[3], Vertex(&vertices)[3]) const;

	std::function<Vertex(Vertex & vertex, Matrix4x4 & model, Matrix4x4 & view, Matrix4x4 & projection)> vertexShader;
	std::function<Vector3(Vertex & vertex, Texture & texture, Material & material)> pixelShader;

	
	// Sends the point into Camera-space
	static void ToCameraSpace(Vector4& point, Vector4& vertex)
	{
		point = vertex / vertex.W;
	}

	// Sends the vertex into Screen-space
	void ToScreenSpace(Vector4& vertex) const
	{
		vertex.X = (vertex.X + 1) * float(width) * 0.5;
		vertex.Y = (vertex.Y + 1) * float(height) * 0.5;
	}

	// Determines if the triangle should be clipped by frustums near-value
	bool ShouldClipNear(Vector4& v1, Vector4& v2, Vector4& v3) const
	{
		return v1.Z < nearplane ||
			   v2.Z < nearplane ||
			   v3.Z < nearplane;
	}

	// Determines if the point is inside of the view-frustum
	static bool OutsideFrustum(Vector4& v)
	{
		return v.X < -1.0f || v.Y < -1.0f ||
			   v.X >  1.0f || v.Y >  1.0f;
	}

	// Determines if the triangle should be kept or discarded depending on the orientation of the face
	static bool CullBackface(const Vector4& v1, const Vector4& v2, const Vector4& v3)
	{
		return v1.Dot((v2 - v1).Cross(v3 - v1)) <= 0.0f;
	}

	// Computes the geometric centroid in the triangle
	static bool Barycentric(const float pX, const float pY, Vector4& a, Vector4& b, Vector4& c, float& den, Vector3& out)
	{
		const float x = ((b.Y - c.Y) * (pX - c.X) + (c.X - b.X) * (pY - c.Y)) * den;
		const float y = ((c.Y - a.Y) * (pX - c.X) + (a.X - c.X) * (pY - c.Y)) * den;
		const float z = 1 - x - y;

		if (x < 0 || y < 0 || z < 0)
			return false;

		out.X = x;
		out.Y = y;
		out.Z = z;

		//assert(out.X + out.Y + out.Z <= 1);
		
		return true;
	}
};
