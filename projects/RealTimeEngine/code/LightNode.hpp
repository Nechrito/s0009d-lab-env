// Copyright © 2020  Philip Lindh 
// All rights reserved

#pragma once
#include "Vector3.h"
#include "Shader.h"
#include "Model.h"

struct Light
{
	Vector3 Color;
	Vector3 Source;
	Vector3 Direction;
};

enum class LightType
{
	DIRECTLIGHT = 0,
	POINTLIGHT  = 1,
	SPOTLIGHT	= 2
};

class LightNode
{
private:

	Model* model = nullptr;
	LightType type;

	Vector3 position;
	Vector3 direction;
	Vector3 color = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 cameraPosition;

	float intensity		  = 1.0f;
	float maxIntensity	  = 2.0f;
	float intensityChange = 1.0f;
	
	float gammaValue	  = 1.0f;

public:

	explicit LightNode(Model* model, const LightType type = LightType::SPOTLIGHT) : model(model), type(type), position(Vector3::Zero()) {}

	void Render(Matrix4x4& view, Matrix4x4& projection, const std::vector<Shader>& entities) const;

	void IncreaseIntensity(float deltaTime);
	void DecreaseIntensity(float deltaTime);

	LightType& GetType()	 { return this->type;		}
	Vector3& GetPosition()	 { return this->position;	}
	Vector3& GetColor()		 { return this->color;		}
	float& GetCurrentGamma() { return this->gammaValue; }

	// Attributes which are sent into the shader
	void SetType(LightType& type)				 { this->type			= type;     }
	void SetCameraPosition(const Vector3 camera) { this->cameraPosition = camera;	}
	void SetPosition(const Vector3 position)	 { this->position		= position; }
	void SetDirection(const Vector3 target)		 { this->direction		= target;   }
	void SetGamma(const float gamma)			 { this->gammaValue		= gamma;	}
	void SetColor(const Vector3 color)			 { this->color			= color;	}
};