#include "VBOTrimmer.h"

void VBOTrimmer::Trim(std::vector<Vector4>& positions, std::vector<Vector4>& normals, std::vector<Vector2>& textureCoords, std::vector<unsigned short>& indexBuffer)
{
	std::map<Vertex, unsigned short> indices;

	std::vector<Vector4> tmpPos = positions;
	std::vector<Vector4> tmpNorm = normals;
	std::vector<Vector2> tmpTex = textureCoords;

	for (unsigned int i = 0; i < positions.size(); i++)
	{
		Vertex vertex = { positions[i], normals[i], textureCoords[i] };

		unsigned short index;

		// adds the vertex which already exists and skips the current duplicate 
		if (IsDuplicate(vertex, indices, index))
		{
			indexBuffer.push_back(index);
		}
		else
		{
			// vertex is relevant, we'll keep it
			tmpPos.push_back(positions[i]);
			tmpTex.push_back(textureCoords[i]);
			tmpNorm.push_back(normals[i]);

			unsigned short next = (unsigned short)tmpPos.size() - 1;
			indexBuffer.push_back(next);
			indices[vertex] = next;
		}
	}

	positions = tmpPos;
	normals = tmpNorm;
	textureCoords = tmpTex;
}

bool VBOTrimmer::IsDuplicate(Vertex& vertex, std::map<Vertex, unsigned short>& vertIndex, unsigned short& result)
{
	const auto vertexIterator = vertIndex.find(vertex);
	if (vertexIterator == vertIndex.end())
		return false;

	result = vertexIterator->second;
	return true;
}