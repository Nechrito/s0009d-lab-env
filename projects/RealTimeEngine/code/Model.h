// Copyright © 2020  Philip Lindh 
// All rights reserved

#pragma once

#include "Matrix4x4.h"
#include "Shader.h"
#include "MeshResource.h"
#include "TextureResource.h"
#include "Transform.h"
#include "MaterialResource.h"

#include "SceneLoader.h"
#include "tiny_gltf.h"

class Model
{
public:
	
	Model() = default;

	Model(const std::string& modelPath, const char* shaderPath, const Vector3 position = Vector3::Zero(), const float scale = 1) { Init(modelPath, shaderPath, position, scale); }
	explicit Model(const std::string& modelPath,				const Vector3 position = Vector3::Zero(), const float scale = 1) { Init(modelPath, "", position, scale); }

	void Draw(Matrix4x4& view, Matrix4x4& projection) const;

	void SetPosition(const Vector3 position) const { this->transform->SetPosition(position); }
	Vector3 GetPosition() const { return this->transform->GetPosition(); }

	void Rotate(float angle) const { this->transform->RotateY(angle); };
	
	// Setters
	void SetTransform(Transform& transform)		 { this->transform		  = std::make_shared<Transform>(transform); }
	void SetMesh(MeshResource& mesh)			 { this->meshResource	  = std::make_shared<MeshResource>(mesh); }
	void SetTexture(TextureResource& texture)	 { this->textureResource  = std::make_shared<TextureResource>(texture); }
	void SetMaterial(MaterialResource& material) { this->materialResource = std::make_shared<MaterialResource>(material); }
	void SetShader(Shader& shader)               { this->shader			  = std::make_shared<Shader>(shader); }

	// Getters
	std::shared_ptr<Transform> GetTransform() const	      { return std::shared_ptr<Transform>(transform); }
	std::shared_ptr<MeshResource> GetMesh() const         { return std::shared_ptr<MeshResource>(meshResource); }
	std::shared_ptr<MaterialResource> GetMaterial() const { return std::shared_ptr<MaterialResource>(materialResource); }
	std::shared_ptr<TextureResource> GetTexture() const   { return std::shared_ptr<TextureResource>(textureResource); }
	std::shared_ptr<Shader> GetShader() const		      { return std::shared_ptr<Shader>(shader); }

	~Model();
	
private:
	bool IsGLTF = false;
	

	std::string directory;
	std::vector<std::string> materialNamesFound;
	
	// Chose the shared_ptr as it's small in size & is fast with insertions/retrievals with strict ownership
	std::shared_ptr<Transform> transform;
	std::shared_ptr<MeshResource> meshResource;
	std::shared_ptr<TextureResource> textureResource;
	std::shared_ptr<MaterialResource> materialResource;
	std::shared_ptr<Shader> shader;

	void Init(const std::string& modelPath, const char* shaderPath, Vector3 position, float scale);
};
