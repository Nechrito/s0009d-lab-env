#pragma once
#include <vector>
#include <map>
#include "Vertex.h"
#include "Vector2.h"

class VBOTrimmer
{
public:
	// Trims the data by removing redundant/duplicate vertices for Pos, UV & Norms that already exists
	// Note: Objects with few vertices may break whilst large models will free a lot of memory 
	static void Trim(std::vector<Vector4>& positions, std::vector<Vector4>& normals, std::vector<Vector2>& textureCoords, std::vector<unsigned short>& indexBuffer);

	// Searches for vertices which already exists in the respective index
	static bool IsDuplicate(Vertex& vertex, std::map<Vertex, unsigned short>& vertIndex, unsigned short& result);
};