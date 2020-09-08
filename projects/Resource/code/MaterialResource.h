#pragma once

#include <string>
#include "Material.h"
#include "Shader.h"

class MaterialResource
{
public:
	std::vector<Material> Materials;

	MaterialResource() = default;

	bool Load(const std::string& path, const std::string& name);
	void Draw(Shader& shader);
	
	~MaterialResource() = default;
};

