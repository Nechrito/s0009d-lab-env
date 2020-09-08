#include "LightNode.h"
#include "Camera.h"

void LightNode::IncreaseIntensity(const float deltaTime)
{
	if (intensity < maxIntensity)
		intensity += intensityChange * deltaTime;
	else 
		intensity = maxIntensity;
}

void LightNode::DecreaseIntensity(const float deltaTime)
{
	if (intensity > 0.01)
		intensity -= intensityChange * deltaTime;
	else
		intensity = 0.01;
}

void LightNode::Render(Matrix4x4& view, Matrix4x4& projection, const std::vector<Shader>& entities) const
{
	if (this->model != nullptr)
	{
		this->model->SetPosition(position);
		this->model->Draw(view, projection);
	}
	
	for (Shader shader : entities)
	{
		shader.Bind();

		shader.SetValue("CameraPosition", cameraPosition);
		shader.SetValue("GammaValue", gammaValue);
		shader.SetValue("LightType", static_cast<int>(type));

		shader.SetValue("light.Position", position);
		shader.SetValue("light.Direction", direction);
		shader.SetValue("light.Color", color);
		shader.SetValue("light.Intensity", intensity);
		
		switch (type)
		{
			case LightType::DIRECTLIGHT:
				shader.SetValue("directAttribs.direction", direction);
				break;
			
			case LightType::POINTLIGHT:
			
				shader.SetValue("pointAttribs.constant", 1.0f);
				shader.SetValue("pointAttribs.linear", 0.14f);
				shader.SetValue("pointAttribs.quadratic", 0.07f);
				break;
			
			case LightType::SPOTLIGHT:
				shader.SetValue("light.Position",  Vector3(0, 4,0));
				shader.SetValue("spotAttribs.direction", Vector3(0, -1, 0));
				shader.SetValue("spotAttribs.constant", 1.0f);
				shader.SetValue("spotAttribs.linear", 0.14f);
				shader.SetValue("spotAttribs.quadratic", 0.07f);
				shader.SetValue("spotAttribs.outerCutOff", DEG2RAD * 17.5f);
				shader.SetValue("spotAttribs.innerCutOff", DEG2RAD * 12.5f);
				break;
		}

		Shader::UnBind();
	}
}