// Copyright © 2020  Philip Lindh 
// All rights reserved

#include "config.h"
#include "Application.h"
#include "Model.h"
#include "LightNode.h"
#include "SoftwareRenderer.h"
#include "Screen.h"
#include "Camera.h"
#include <cmath>

Application::Application()
{
	// window
	this->window = nullptr;
	this->windowTitle = this->baseTitleString = "Philip Lindh | Check The Console! | ";

	// camera
	Camera::Instance().SetViewport(width, height);
	Camera::Instance().SetFieldOfView(65.0f, 0.1f, 10.0f);
	Camera::Instance().SetPosition(Vector3(0, -4, -8));
}

bool Application::Open()
{
	App::Open();

	// Initialize window with a set of rules
	this->window = new Display::Window;
	this->window->SetSize(width, height);
	this->window->SetTitle(windowTitle);

	// Subscribe to callback functions
	this->window->SetMouseMoveFunction([this] (const double x, const double y)
	{
		Camera::Instance().Rotate(width * 0.5 - x, height * 0.5 - y);
		this->window->SetCursorPosition(width * 0.5, height * 0.5);
	});

	this->window->SetMouseScrollFunction([] (float x, const float y)
	{
		Camera::Instance().Zoom(y);
	});

	this->window->SetKeyPressFunction([this] (int32, const int32 button, const int32 action, int32)
	{
		const auto iterator = find(cachedKeys.begin(), cachedKeys.end(), button);

		if (action == 0)
		{
			if (iterator != cachedKeys.end()) // clear all cached keys which have been released
				cachedKeys.erase(iterator);
		}
		else if (iterator == cachedKeys.end()) // insert new pushed down key 
			cachedKeys.push_back(button);

		// released shift
		if (action == 0 && sprint && button == 50)
			sprint = false;

		// current key isn't being pressed, boring 
		if (action != 1)
			return;

		switch (button)
		{
			case 9: exit(0); /*this->window->Close();*/ break; // Esc

			case 11: rotateModel = !rotateModel; break; // 2
			case 14: cpuRender   = !cpuRender;   break; // 5
			case 50: sprint = !sprint;  break; // Shift
			
			case 10: // 1
			{
				drawWireframe = !drawWireframe;
					
				if (drawWireframe)
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				else
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			break;
			
			case 12: // 3
			{
				if (cpuRender)
				{
					std::cout << "Sorry, the light type is currently enforced for CPU-Rendering\n";
					return;
				}
					
				const int next = int(activeLightType) + 1;
				const int index = next >= 3 ? 0 : next;
				this->activeLightType = LightType(index);
			}
			break;
			
			case 13: // 4
				{
					for (auto& light : lightNodes)
					{
						if (light.GetCurrentGamma() == 1.0f)
							light.SetGamma(1.6f);
						else
							light.SetGamma(1.0f);
					}
				}
			break;

			case 24: Camera::Instance().SetCameraMode(CameraMode::ORBIT);    break; // Q
			case 26: Camera::Instance().SetCameraMode(CameraMode::FREELOOK); break; // E
			case 27: Camera::Instance().SetCameraMode(CameraMode::FORCED);   break; // R
		}
	});

	return this->window->Open();
}

void Application::Run()
{
	// Hides unseen faces through culling, can be seen through wireframe-mode 
	glEnable(GL_DEPTH_TEST);
  	glDepthFunc(GL_LESS);

  	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  	glEnable(GL_BLEND);

	// Models
	Model* lightModel  = new Model("models/Sun/cube.obj", "shaders/model.glsl", Vector3(0, 12, 10));
	Model* landscape   = new Model("models/Landscape/landscape.obj", "shaders/phong.glsl");
	//Model* targetModel = new Model("models/Fox/Fox.obj", "shaders/phong.glsl", Vector3(0, 0.1, 0));
	Model* targetModel = new Model("models/FoxGLTF/Fox.gltf", "shaders/phong.glsl", Vector3(0, 0.1, 0));

	// Lights
	this->lightNodes.emplace_back(lightModel, LightType::SPOTLIGHT);
	this->lightNodes.emplace_back(lightModel, LightType::POINTLIGHT);
	this->lightNodes.emplace_back(lightModel, LightType::DIRECTLIGHT);

	// Shaders
	const auto vertexShader = [] (Vertex& vertex, Matrix4x4& model, Matrix4x4& view, Matrix4x4& projection) -> Vertex
	{
		const Vector4 position = (projection * view * model).Transpose() * vertex.Position;
		return { position, vertex.Normal, vertex.TextureCoordinates };
	};
	
	const auto fragmentShader = [this] (Vertex& vertex, Texture& texture, Material& material) -> Vector3
	{
		const Vector3 textureColor = TextureResource::GetTextureColor(texture, vertex.TextureCoordinates);
		//return textureColor; // <-- Un-Comment this to discard lightning
		const Vector3 vPosition = vertex.Position.To3D();
		const Vector3 cPosition = Camera::Instance().GetPosition();
		
		Vector3 result;
		Vector3 lPosition;
		Vector3 lightColor;
		
		for (LightNode& light : lightNodes)
		{
			if (light.GetType() != this->activeLightType)
			{
				continue;
			}
			
			lPosition = light.GetPosition();
			lightColor = light.GetColor();
		}

		const Vector3 lightDir = (lPosition - vPosition).Normalized();
		const Vector3 normal = vertex.Normal.Normalized().To3D();
		const Vector3 viewDir = (cPosition - vPosition).Normalized();

		Vector3 ambient = lightColor * material.Ambient;

		Vector3 diffuse = lightColor * material.Diffuse * std::max(normal.Dot(lightDir), 0.0f);

		const Vector3 reflection = (lightDir * -1).Reflect(normal);
		const float specularValue = CMath::Saturate(viewDir.Dot(reflection));
		const float lambertian = CMath::Pow(specularValue, material.SpecularExponent);
		Vector3 specular = lightColor * material.Specular * lambertian;

		const float distance = lPosition.Distance(vPosition);
		const float attenuation = 1.0f / (1.0f + 0.14f * distance + 0.07f * (distance * distance));

		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;

		const Vector3 combined = ambient + diffuse + specular;
		result += Vector3::Saturate(combined);

		return result * textureColor;
	};

	// Software-renderer
	SoftwareRenderer renderer;
	renderer.SetVertexShader(vertexShader);
	renderer.SetPixelShader(fragmentShader);

	// Node-container for objects we'd like to render
	Screen screen(renderer);
	screen.AddRenderableObject(lightModel);
	screen.AddRenderableObject(targetModel);
	screen.AddRenderableObject(landscape);
	
	// Entities referenced shader
	std::vector<Shader> shaders;
	shaders.push_back(*targetModel->GetShader());
	shaders.push_back(*landscape->GetShader());

	// Force-centre the cursor when done loading
	this->window->SetCursorPosition(width * 0.5, height * 0.5);
	this->window->SetCursorVisibility(false);
	
	// Prints a simple input guide to the console
	std::cout << "\n-----KEYBOARD INPUT-----\n";

	std::cout << "Escape: Quits the application\n";
	std::cout << "1: Toggle Wireframe\n";
	std::cout << "2: Toggle Model Rotation\n";
	std::cout << "3: Change Active Light\n";
	std::cout << "4: Toggle Gamma\n";
	std::cout << "5: Toggle Render (CPU / GPU)\n";
	std::cout << "\n";

	std::cout << "Arrow Up:   Increase Light Intensity\n";
	std::cout << "Arrow Down: Decrease Light Intensity\n";
	std::cout << "\n";

	std::cout << "Q: Camera Orbit\n";
	std::cout << "E: Camera Free-look\n";
	std::cout << "R: Camera Look At Target\n";

	std::cout << "---------LINUX----------\n";

	// time since launch, used for computing the fps
	// todo: can be changed to CMath, but gotta debug to determine which is faster
	double start = glfwGetTime();
	
	while (this->window->IsOpen())
	{
		// Processes callback functions such as keyboard/mouse input
		this->window->Update();

		// Clear screen
		glClearColor(0.5f, 0.3f, 0.65f, 1);

		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Adding one frame for each iteration
		this->frameCount++;

		// Keys which are currently being pressed
		for (auto& key : cachedKeys)
		{
			switch (key)
			{ 
				case 25: Camera::Instance().Translate(CameraDirection::FORWARD, deltaTime, sprint);  break; // W
				case 38: Camera::Instance().Translate(CameraDirection::LEFT, deltaTime, sprint);     break; // A
				case 39: Camera::Instance().Translate(CameraDirection::BACKWARD, deltaTime, sprint); break; // S
				case 40: Camera::Instance().Translate(CameraDirection::RIGHT, deltaTime, sprint);    break; // D
				
				case 111: for (auto& light : lightNodes) light.IncreaseIntensity(deltaTime); break; // Up
				case 116: for (auto& light : lightNodes) light.DecreaseIntensity(deltaTime); break; // Down
			}
		}

		// Rotation
		if (this->rotateModel)
		{
			targetModel->Rotate(deltaTime * 50);
		}

		// Set direction towards the targeted model
		Vector3 targetPosition = targetModel->GetPosition();
		Camera::Instance().SetTarget(targetPosition);
		
		// Fetch what makes up the camera-perspective by far/near - plane
		Matrix4x4 view = Camera::Instance().View(currentTime);
		Matrix4x4 projection = Camera::Instance().Projection();
		
		for (auto& light : lightNodes)
		{
			if (light.GetType() != this->activeLightType)
			{
				continue;
			}

			if (light.GetType() == LightType::POINTLIGHT)
			{
				const auto orbitRadius = 10;
				const auto lightSpeed = 0.65;
				const auto orbitX = sin(currentTime * lightSpeed) * orbitRadius;
				const auto orbitZ = cos(currentTime * lightSpeed) * orbitRadius;

				light.SetPosition(Vector3(orbitX, 5, orbitZ) + targetPosition);
				light.SetDirection(targetPosition);
			}

			light.SetCameraPosition(Camera::Instance().GetPosition());
			light.Render(view, projection, shaders);
		}
		
		// Render
		if (this->cpuRender)
		{
			screen.Draw(view, projection);
		}
		else
		{
			targetModel->Draw(view, projection);
			landscape->Draw(view, projection);
		}

		// Swaps front & back buffers of the window
		this->window->SwapBuffers();

		// Time between current and previous frame, useful to limit movement as compute speed differs with unlocked frame-rate
		// Can also be used for timers
		this->currentTime = glfwGetTime();
		this->deltaTime = currentTime - lastFrame;
		this->lastFrame = currentTime;
		
		// FPS counter
		const double timeElapsed = currentTime - start;
		
		if (timeElapsed >= 0.5) 
		{
			this->fps = frameCount / timeElapsed;

			std::string selectedLight;
			switch (activeLightType)
			{
				case LightType::DIRECTLIGHT: selectedLight = "DirectLight"; break;
				case LightType::POINTLIGHT:  selectedLight = "PointLight";  break;
				case LightType::SPOTLIGHT:   selectedLight = "SpotLight";   break;
			}

			std::string fpsFormatted = fps <= 10 ? CString::FormatString("%.1f", fps) : CString::FormatString("%.0f", fps);
		
			std::string title = windowTitle.append(selectedLight).append(" | FPS: ").append(fpsFormatted);

			this->window->SetTitle(title);
			this->windowTitle = this->baseTitleString;

			this->frameCount = 0;
			start = glfwGetTime();

		}
	}

	delete targetModel;
	delete landscape;
}

