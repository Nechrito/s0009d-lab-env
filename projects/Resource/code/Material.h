#pragma once
#include <string>
#include "Vector3.h"

struct Material
{
	std::string Path;
	std::string Name;
	
	Vector3 Ambient;
	Vector3 Diffuse;
	Vector3 Specular;

	float SpecularExponent;
	float OpticalDensity;
	float Dissolve;
	float Illumination;
};
