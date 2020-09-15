// Copyright © 2020  Philip Lindh 
// All rights reserved

#include "MaterialResource.h"
#include <fstream>
#include "CString.h"

bool MaterialResource::Load(const std::string& path, const std::string& name)
{
	std::ifstream file(path);

	if (!file.is_open())
	{
		std::cout << "Failed to open " << path << "\n";
		return false;
	}

	std::cout << "Loading: " << path << "\n";

	Material ref;
	ref.Name = name;
	ref.Path = path;

	std::string line;
	
	while (getline(file, line))
	{
		auto lineSplit = CString::Split(line, ' ');

		if (lineSplit.size() <= 1)
			continue;

		if (lineSplit[0] == "Ka")
		{
			ref.Ambient.X = stof(CString::Split(lineSplit[1], ' ')[0]);
			ref.Ambient.Y = stof(CString::Split(lineSplit[2], ' ')[0]);
			ref.Ambient.Z = stof(CString::Split(lineSplit[3], ' ')[0]);
		}
		else if (lineSplit[0] == "Kd")
		{
			ref.Diffuse.X = stof(CString::Split(lineSplit[1], ' ')[0]);
			ref.Diffuse.Y = stof(CString::Split(lineSplit[2], ' ')[0]);
			ref.Diffuse.Z = stof(CString::Split(lineSplit[3], ' ')[0]);
		}
		else if (lineSplit[0] == "Ks")
		{
			ref.Specular.X = stof(CString::Split(lineSplit[1], ' ')[0]);
			ref.Specular.Y = stof(CString::Split(lineSplit[2], ' ')[0]);
			ref.Specular.Z = stof(CString::Split(lineSplit[3], ' ')[0]);
		}
		else if (lineSplit[0] == "Ns")
			ref.SpecularExponent = stof(lineSplit[1]);
		else if (lineSplit[0] == "Ni")
			ref.OpticalDensity = stof(lineSplit[1]);
		else if (lineSplit[0] == "d")
			ref.Dissolve = stof(lineSplit[1]);
		else if (lineSplit[0] == "illum")
			ref.Illumination = stof(lineSplit[1]);
	}

	Materials.push_back(ref);
	
	file.close();
	
	return true;
}

void MaterialResource::Draw(Shader& shader)
{
	for (const Material& material : Materials)
	{
		shader.SetValue("material.AmbientColor", material.Ambient);
		shader.SetValue("material.DiffuseColor", material.Diffuse);
		shader.SetValue("material.SpecularColor", material.Specular);
		shader.SetValue("material.SpecularExponent", material.SpecularExponent);
	}
}
