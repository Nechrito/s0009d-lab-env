#pragma once
#include <Vector2.h>
#include "Vector4.h"
#include <cstring>

struct Vertex
{
	Vector4 Position;
	Vector4 Normal;
	Vector2 TextureCoordinates;

	bool operator<(const Vertex vertex) const
	{
		// Compares the memory blocks for an un-matching byte 
		return memcmp((void*)this, (void*)& vertex, sizeof(Vertex)) > 0;
	};
};
