// Copyright © 2020  Philip Lindh 
// All rights reserved

#include "Model.h"
#include "CString.h"
#include "LightNode.h"
#include <memory>

void Model::Init(const std::string& modelPath, const char* shaderPath, Vector3 position, float scale)
{
	this->directory = CString::ExcludeFileFromPath(modelPath);
	
	std::cout << "Loading: " << CString::RetrieveFilesOfType(directory, ".obj")[0] << "\n";

	this->transform			= std::make_shared<Transform>();
	this->meshResource		= std::make_shared<MeshResource>();
	this->textureResource	= std::make_shared<TextureResource>();
	this->materialResource  = std::make_shared<MaterialResource>();
	this->shader			= std::make_shared<Shader>(shaderPath);

	transform->SetPosition(position);
	transform->SetScale(scale);

	std::vector<std::string> textureFiles  = CString::RetrieveFilesOfType(directory, ".png");
	std::vector<std::string> materialFiles = CString::RetrieveFilesOfType(directory, ".mtl");

	const std::string basespec = "base_diff.png";
	const auto baseTexture = find(textureFiles.begin(), textureFiles.end(), basespec);

	if (baseTexture != textureFiles.end())
		textureResource->Load(directory + *baseTexture, 1);

	for (const std::string& material : materialFiles)
		materialResource->Load(directory + material, material);

	meshResource->Load(modelPath);
}

void Model::Draw(Matrix4x4& view, Matrix4x4& projection) const
{
	Matrix4x4 model = transform->Transformation();
	const Matrix4x4 modelView = view * model;

	shader->Bind();
	shader->SetValue("Projection", projection);
	shader->SetValue("ModelView", modelView);
	shader->SetValue("Model", model);
	
	textureResource->Draw(*shader);
	materialResource->Draw(*shader);
	meshResource->Draw();

	shader->UnBind();
	textureResource->Unbind();
}

Model::~Model()
{
	textureResource->Destroy();
	meshResource->Destroy();
}
