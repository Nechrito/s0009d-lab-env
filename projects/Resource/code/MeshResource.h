// Copyright © 2020  Philip Lindh 
// All rights reserved

#pragma once

#include "core/app.h"

#include <string>
#include <vector>

#include "CString.h"
#include "Vector2.h"
#include "Vector4.h"
#include "Vertex.h"

class MeshResource
{
public:
	std::vector<unsigned int> VertexIndices;
	std::vector<unsigned short> IndexBuffer;

	std::vector<Vertex> Vertices;
	
	bool Load(const std::string& path);

	void Draw()    const;
	void Destroy() const;

private:
	std::vector<Vector4> normals;
	std::vector<Vector2> textureCoordinates;
	std::vector<Vector4> positions;
	
	unsigned int vertexBuffer;
	unsigned int positionBuffer;
	unsigned int normalBuffer;
	unsigned int textureBuffer;
	
	std::vector<std::string> materialNames;
	
	bool ReadObj(const std::string& path);
	void Link();
};

