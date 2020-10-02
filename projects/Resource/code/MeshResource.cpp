// Copyright © 2020  Philip Lindh 
// All rights reserved

#include "MeshResource.h"

#include <fstream>
#include "VBOTrimmer.h"


bool MeshResource::Load(const std::string& path)
{
	if (ReadObj(path))
	{
		Link();
		return true;
	}
	return false;
}

void MeshResource::Draw() const
{

	if (isGLTF)
	{

		return;
	}

	// vertex Positions
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, nullptr);

	// vertex normals
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, nullptr);

	// texture coordinates 
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, nullptr);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffer);
	glDrawElements(GL_TRIANGLES, IndexBuffer.size(), GL_UNSIGNED_SHORT, nullptr);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void MeshResource::Destroy() const
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &positionBuffer);
	glDeleteBuffers(1, &normalBuffer);
	glDeleteBuffers(1, &textureBuffer);
}

void MeshResource::Link()
{
	// prevents duplicates of vertices and simply reuses them instead
	VBOTrimmer::Trim(positions, normals, textureCoordinates, IndexBuffer);

	// Binds the buffer arrays 
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(Vector4), &positions[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(Vector4), &normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, textureCoordinates.size() * sizeof(Vector2), &textureCoordinates[0], GL_STATIC_DRAW);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer.size() * sizeof(unsigned short), &IndexBuffer[0], GL_STATIC_DRAW);
}

bool MeshResource::ReadObj(const std::string& path)
{
	if (CString::FileType(path) != ".obj")
	{
		std::cout << "Invalid format, this is not an .obj file " << path << "\n";
		return false;
	}

	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cout << "Failed to find the requested file: " << path << "\n";
		return false;
	}

	std::cout << "Loading: " << path << "\n";
	auto start = CMath::CurrentTime();

	// temp to fill vertices properly
	std::vector<unsigned int> textureIndices;
	std::vector<unsigned int> normalIndices;

	std::vector<Vector4> tmpVerts;
	std::vector<Vector2> tmpTextureCoords;
	std::vector<Vector4> tmpNormals;

	std::string line;

	while (getline(file, line))
	{
		if (line.empty())
			continue;

		auto lineSplit = CString::Split(line, ' ');

		if (lineSplit[0] == "mtllib") // material name
		{
			materialNames.push_back(lineSplit[1]);
		}
		else if (lineSplit[0] == "v") // vertex position
		{
			Vector4 vertex;
			vertex.X = stof(lineSplit[1]);
			vertex.Y = stof(lineSplit[2]);
			vertex.Z = stof(lineSplit[3]);
			tmpVerts.push_back(vertex);
		}
		else if (lineSplit[0] == "vt") // texture coordinate
		{
			Vector2 vertex;
			vertex.X = stof(lineSplit[1]);
			vertex.Y = 1 - stof(lineSplit[2]);
			tmpTextureCoords.push_back(vertex);
		}
		else if (lineSplit[0] == "vn") // normal
		{
			Vector4 vertex;
			vertex.X = stof(lineSplit[1]);
			vertex.Y = stof(lineSplit[2]);
			vertex.Z = stof(lineSplit[3]);
			tmpNormals.push_back(vertex);
		}
		else if (lineSplit[0] == "f") //  face 
		{
			std::vector<std::string> v1 = CString::Split(lineSplit[1], '/');
			std::vector<std::string> v2 = CString::Split(lineSplit[2], '/');
			std::vector<std::string> v3 = CString::Split(lineSplit[3], '/');

			VertexIndices.push_back(stoi(v1[0]) - 1);
			VertexIndices.push_back(stoi(v2[0]) - 1);
			VertexIndices.push_back(stoi(v3[0]) - 1);

			textureIndices.push_back(stoi(v1[1]) - 1);
			textureIndices.push_back(stoi(v2[1]) - 1);
			textureIndices.push_back(stoi(v3[1]) - 1);

			normalIndices.push_back(stoi(v1[2]) - 1);
			normalIndices.push_back(stoi(v2[2]) - 1);
			normalIndices.push_back(stoi(v3[2]) - 1);
		}
	}
	file.close();

	for (unsigned int i = 0; i < VertexIndices.size(); i++)
	{
		unsigned int vertexIndex = VertexIndices[i];
		unsigned int textureIndex = textureIndices[i];
		unsigned int normalIndex = normalIndices[i];

		positions.push_back(tmpVerts[vertexIndex]);
		textureCoordinates.push_back(tmpTextureCoords[textureIndex]);
		normals.push_back(tmpNormals[normalIndex]);

		Vertex vertex {tmpVerts[vertexIndex],  tmpNormals[normalIndex], tmpTextureCoords[textureIndex] };
		Vertices.push_back(vertex);
	}

	printf("Found %d Vertices ", static_cast<int>(VertexIndices.size()));
	printf("in %f seconds\n\n", CMath::TimeSince(start));
	
	return true;
}