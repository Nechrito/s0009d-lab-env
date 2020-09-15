// Copyright © 2020  Philip Lindh 
// All rights reserved

#pragma once

#include "Shader.h"
#include "TextureResource.h"
#include "SoftwareRenderer.h"

class Screen
{
public:
	explicit Screen(SoftwareRenderer& renderer);
	void Draw(Matrix4x4& view, Matrix4x4& projection);
	void AddRenderableObject(Model* model);
	
private:
	unsigned int id;
	SoftwareRenderer renderer;
	Shader shader;
	TextureResource textureResource;
	Texture texture;
};

inline Screen::Screen(SoftwareRenderer& renderer)
{
	this->renderer = renderer;

	glGenVertexArrays(1, &id);

	texture = TextureResource::Create(renderer.GetWidth(), renderer.GetHeight(), renderer.GetPtr());

	shader = Shader("shaders/screen.glsl");
}

inline void Screen::Draw(Matrix4x4& view, Matrix4x4& projection)
{
	glBindVertexArray(id);

	renderer.Draw(view, projection);
	TextureResource::Update(texture, renderer.GetPtr());

	shader.Bind();
	TextureResource::Bind(texture);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	Shader::UnBind();
	TextureResource::Unbind();

	//renderer.ClearBuffers();
}

inline void Screen::AddRenderableObject(Model* model)
{
	RenderableObject obj(model->GetMesh(), model->GetMaterial(), model->GetTexture(), model->GetTransform());
	renderer.AddRenderableObject(obj);
}
