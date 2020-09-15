// Copyright © 2020  Philip Lindh 
// All rights reserved

#pragma once

#include "render/window.h"

#include <vector>
#include "LightNode.h"

class Application final : public Core::App
{
public:
	Application();

	bool Open()  override;
	void Run()	 override;
	void Close() override {}
	void Exit()  override {}

	~Application() = default;
	
private:
	
	// window wrapper 
	Display::Window* window;
	std::string windowTitle;
	std::string baseTitleString;

	// viewport 
	int width = 1280;
	int height = 720;

	// pressed keys
	std::vector<int> cachedKeys;
	
	// lights
	std::vector<LightNode> lightNodes;
	LightType activeLightType = LightType::SPOTLIGHT;
	
	// engine
	int frameCount = 0;
	double fps = 0;

	float deltaTime = 0;
	double currentTime = 0;
	float lastFrame = 0;

	// menu items
	bool drawWireframe = false;
	bool rotateModel = false;
	bool sprint = false;
	bool cpuRender = true;
};
