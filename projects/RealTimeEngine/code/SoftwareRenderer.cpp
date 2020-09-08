#include "SoftwareRenderer.h"
#include "Camera.h"

SoftwareRenderer::SoftwareRenderer()
{
	this->width = int(Camera::Instance().Width);
	this->height = int(Camera::Instance().Height);

	pixelWidth = 2.0f / static_cast<float>(width);
	pixelHeight = 2.0f / static_cast<float>(height);
	
	this->size = width * height;

	this->farplane = Camera::Instance().Far;
	this->nearplane = Camera::Instance().Near;

	this->backgroundColor = PixelColor(static_cast<char>(153), static_cast<char>(75), static_cast<char>(179));

	this->framebuffer = new PixelColor[size];
	this->depthbuffer = new float[size];
}

void SoftwareRenderer::ClearBuffers() const
{
	std::fill(framebuffer, framebuffer + size, backgroundColor);
	std::fill(depthbuffer, depthbuffer + size, farplane);
}

void SoftwareRenderer::SetPixel(const int x, const int y, Vector3& color) const
{
	const int index = x + y * width;
	framebuffer[index].R = static_cast<unsigned char>(255 * color.X);
	framebuffer[index].G = static_cast<unsigned char>(255 * color.Y);
	framebuffer[index].B = static_cast<unsigned char>(255 * color.Z);
}

void SoftwareRenderer::Draw(Matrix4x4& view, Matrix4x4& projection)
{
	ClearBuffers();

	for (auto& target : targets)
	{
		//auto start = CMath::CurrentTime();

		Matrix4x4 model = target.TransformRes->Transformation();

		auto mesh = target.MeshRes;

		for (size_t i = 0; i < mesh->VertexIndices.size(); i += 3)
		{
			// Local-space to View-space
			Vertex vertices[3]
			{
				vertexShader(mesh->Vertices[i + 0], model, view, projection),
				vertexShader(mesh->Vertices[i + 1], model, view, projection),
				vertexShader(mesh->Vertices[i + 2], model, view, projection),
			};

			// Near-plane clipping
			if (ShouldClipNear(vertices[0].Position, vertices[1].Position, vertices[2].Position))
			{
				continue;
			}

			Vector4 points[3];
			for (int j = 0; j < 3; ++j)
			{
				ToCameraSpace(points[j], vertices[j].Position);
			}

			// Frustum clipping
			if (OutsideFrustum(points[0]) && OutsideFrustum(points[1]) && OutsideFrustum(points[2]))
			{
				continue;
			}

			// Back-face culling
			if (CullBackface(points[0], points[1], points[2]))
			{
				continue;
			}

			// Computes the world-to-screen coordinates
			for (auto& point : points)
			{
				ToScreenSpace(point);
			}

			FillTriangle(target, points, vertices);
		}

		//printf("\rRasterized model in %f Seconds", CMath::TimeSince(start));
	}
}

void SoftwareRenderer::FillTriangle(RenderableObject& target, Vector4(&points)[3], Vertex(&vertices)[3]) const
{
	Vector4* v1 = &points[0];
	Vector4* v2 = &points[1];
	Vector4* v3 = &points[2];

	v1->Y = std::round(v1->Y);
	v2->Y = std::round(v2->Y);
	v3->Y = std::round(v3->Y);

	if (v1->Y > v2->Y) std::swap(v1, v2);
	if (v2->Y > v3->Y) std::swap(v2, v3);
	if (v1->Y > v2->Y) std::swap(v1, v2);

	// The connecting lines that define the triangle
	Line l1(v1, v3);
	Line l2(v1, v2);
	Line l3(v2, v3);

	FillOutline(target, points, vertices, l1);

	FillOutline(target, points, vertices, l2);

	FillOutline(target, points, vertices, l3);
}

void SoftwareRenderer::FillOutline(RenderableObject& target, Vector4(&points)[3], Vertex(&vertices)[3], Line& line) const
{
	if (std::abs(line.dy2) <= 0)
	{

	}
	//vertex.X = (vertex.X + 1) * float(width) * 0.5;
	//float fy = 2.0f * pixelHeight * static_cast<float>(line.currentY) - 1.0f/* + 0.5f * pixelHeight*/;
	while (line.currentY < line.y2)
	{
		FillHorizontalLine(target, points, vertices, line.x1, line.currentY, line.x2);

		// Slope error reached limit, time to 
		// increment y and update slope 
		if (line.fraction >= 0)
		{
			line.currentY++;
			line.fraction += line.dy2 - line.dx2;
		}
		else
		{
			// Add slope to increment angle formed 
			line.fraction += line.dy2;
		}
		line.currentX++;
	}
}

void SoftwareRenderer::FillHorizontalLine(RenderableObject& target, Vector4(&points)[3], Vertex(&vertices)[3], int x1, int y, int x2) const
{
	// Out of height-boundss
	if (y < 0 || y >= height)
	{
		return;
	}

	// pre-calculations for the coefficient in the barycentric coordinate-system
	Vector3 coeff;
	
	float denominator = ((points[1].Y - points[2].Y) * (points[0].X - points[2].X) + (points[2].X - points[1].X) * (points[0].Y - points[2].Y));
	if (denominator == 0)
		denominator = 0;
	else
		denominator = 1 / denominator;
	
	// We start from left vertex progressing through towards the rightmost vertex
	if (x1 > x2)
	{
		std::swap(x1, x2);
	}

	//float fx = 2.0f * pixelWidth * static_cast<float>(x1) - 1.0f/* + 0.5f * pixelWidth*/;
	
	// Iterate through the pixels in the line for the current scanline 
	for (auto x = x1; x <= x2; ++x)
	{
		// Out of width-bounds
		if (x >= width || x < 0)
		{
			continue;
		}

		// Compute the coefficient 
		if (!Barycentric(x, y, points[0], points[1], points[2], denominator, coeff))
		{
			continue;
		}

		
		// The depth value of the current point
		const float z = points[0].Z * coeff.X + points[1].Z * coeff.Y + points[2].Z * coeff.Z;

		const int index = x + width * y;

		if (z < depthbuffer[index])
		{
			// Cache the depth until the frame is over with
			depthbuffer[index] = z;

			// Interpolation
			const Vector4 vPosition = vertices[0].Position * coeff.X + vertices[1].Position * coeff.Y + vertices[2].Position * coeff.Z;
			const Vector4 vNormal = vertices[0].Normal * coeff.X + vertices[1].Normal * coeff.Y + vertices[2].Normal * coeff.Z;
			const Vector2 vTextureCoordinates
			{
				vertices[0].TextureCoordinates.X * coeff.X + vertices[1].TextureCoordinates.X * coeff.Y + vertices[2].TextureCoordinates.X * coeff.Z,
				vertices[0].TextureCoordinates.Y * coeff.X + vertices[1].TextureCoordinates.Y * coeff.Y + vertices[2].TextureCoordinates.Y * coeff.Z
			};

			Vertex vertex{ vPosition, vNormal, vTextureCoordinates };

			Vector3 color = pixelShader(vertex, target.TextureRes->Textures[0], target.MaterialRes->Materials[0]);

			SetPixel(x, y, color);
		}

		//fx += pixelWidth;
	}
}