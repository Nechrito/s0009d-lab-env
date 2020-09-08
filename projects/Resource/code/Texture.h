#pragma once
#include <string>

struct Texture
{
	unsigned char* Handle;
	unsigned int TextureId;
	int Height;
	int Width;
	int Components;
	int Layer;
	int Format;
	std::string Path;
	std::string Type;
};
