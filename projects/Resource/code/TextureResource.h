#pragma once
#include <string>
#include "Shader.h"
#include "Texture.h"
#include "Vector2.h"

struct PixelColor
{
	unsigned char R = 0;
	unsigned char G = 0;
	unsigned char B = 0;

	PixelColor(const char red, const char green, const char blue)
	{
		this->R = red;
		this->G = green;
		this->B = blue;
	}

	explicit PixelColor(const char value)
	{
		this->R = value;
		this->G = value;
		this->B = value;
	}

	PixelColor()
	{
		this->R = 0;
		this->G = 0;
		this->B = 0;
	}

};

class TextureResource
{
public:
	std::vector<Texture> Textures;

	bool Load(const std::string& path, int layer);
	static Texture Create(int width, int height, PixelColor* buffer);
	
	void Draw(Shader& shader);

	static void Update(Texture& ref, PixelColor* data);

	static void Bind(Texture& ref);
	static void Unbind();
	
	static Vector3 GetTextureColor(const Texture& ref, Vector2& uv);
	static std::string GetTextureType(const std::string& file);

	void Destroy();


	~TextureResource() = default;
};

