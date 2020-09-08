#include "TextureResource.h"

#include "core/app.h"
#include <stb_image.h>
#include <ostream>
#include <iostream>
#include "CString.h"

bool TextureResource::Load(const std::string& path, const int layer)
{
	std::cout << "Loading: " << path << "\n";

	Texture ref;

	ref.Path = path;
	ref.Type = GetTextureType(path); 
	ref.Layer = layer;

	ref.Handle = stbi_load(path.c_str(), &ref.Width, &ref.Height, &ref.Components, 3);

	if (ref.Handle)
	{
		// Stores '1' texture to the specified array
		glGenTextures(1, &ref.TextureId);

		glBindTexture(GL_TEXTURE_2D, ref.TextureId);

		int format = 0;
		switch (ref.Components)
		{
			case 1: format = GL_ALPHA;     break;
			case 2: format = GL_LUMINANCE; break;
			case 3: format = GL_RGB;       break;
			case 4: format = GL_RGBA;      break;
		}
		ref.Format = format;

		// TODO: Level is increased for multi-texture rendering, add dynamic format 
		glTexImage2D(GL_TEXTURE_2D, 0, ref.Format, ref.Width, ref.Height, 0, ref.Format, GL_UNSIGNED_BYTE, ref.Handle);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Filters, pixel-selection 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Wrappers
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// we wont need this anymore
		glBindTexture(GL_TEXTURE_2D, 0);

		Textures.push_back(ref);

		return true;
	}

	std::cout << "Failed to load the texture " << path << "\n";
	
	stbi_image_free(ref.Handle);
	
	return false;
}

Texture TextureResource::Create(const int width, const int height, PixelColor* buffer)
{
	Texture texture;
	glGenTextures(1, &texture.TextureId);
	glBindTexture(GL_TEXTURE_2D, texture.TextureId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glBindTexture(GL_TEXTURE_2D, 0);

	texture.Width = width;
	texture.Height = height;
	texture.Layer = 0;
	texture.Format = GL_RGB;
	texture.Components = 4;
	texture.Handle = nullptr;
	
	return texture;
}

void TextureResource::Update(Texture& ref, PixelColor* data)
{
	glBindTexture(GL_TEXTURE_2D, ref.TextureId);
	
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, ref.Width, ref.Height, ref.Format, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureResource::Bind(Texture& ref)
{
	glActiveTexture(GL_TEXTURE0 + ref.Layer);
	glBindTexture(GL_TEXTURE_2D, ref.TextureId);
}

void TextureResource::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureResource::Draw(Shader& shader)
{
	for (auto& texture : Textures)
	{
		Bind(texture);
		shader.SetValue("textures." + texture.Type, texture.Layer);
	}
}

Vector3 TextureResource::GetTextureColor(const Texture& ref, Vector2& uv)
{
	const int x = static_cast<int>(static_cast<float>(ref.Width) * uv.X) % ref.Width;
	const int y = static_cast<int>(static_cast<float>(ref.Height) * uv.Y) % ref.Height;
	const unsigned char* channels = &ref.Handle[(x + ref.Width * y) * ref.Components];

	const float bitColor = 1.0f / 255;
	
	return
	{
		static_cast<float>(channels[0]) * bitColor,
		static_cast<float>(channels[1]) * bitColor,
		static_cast<float>(channels[2]) * bitColor
	};
}

void TextureResource::Destroy()
{
	for (Texture& texture : Textures)
	{
		glDeleteTextures(1, &texture.TextureId);
	}
}

std::string TextureResource::GetTextureType(const std::string& file)
{
	const std::string filename = CString::GetFileFromFullPath(file);
	
	if (filename.find("_diff"))
		return "Diffuse";
	
	if (filename.find("_ddn"))
		return "Normal";

	if (filename.find("_spec"))
		return "Specular";

	if (filename.find("_msk"))
		return "Mask";

	return "UNKNOWN";
}
