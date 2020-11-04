// Copyright © 2020  Philip Lindh 
// All rights reserved

#pragma once

#include "Matrix4x4.h"
#include "Vector3.h"
#include "Transform.h"

enum class CameraMode
{
	FREELOOK,
	ORBIT,
	FORCED,
};

enum class CameraDirection
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
private:
	Transform transform;
	CameraMode activeMode;
	Vector3 target; // where camera will try to look at

	float currentFov = 65;
	float maxFov;
	float yaw = -90.0;
	float pitch = 0.0;

protected:
	Camera();
	
public:

	// Singleton instantiation assuming project is single-threaded 
	static Camera& Instance()
	{
		static Camera instance;
		return instance;
	}
	
	// Direction coords
	Vector3 CameraX;
	Vector3 CameraY;
	Vector3 CameraZ;

	// Universal, yet initialized by Application.h 
	int Width;
	int Height;

	// View-plane
	float Near;
	float Far;

	void SetFieldOfView(float fov, float near, float far);
	void SetViewport(int width, int height);
	void SetTarget(Vector3 target);
	void SetCameraMode(CameraMode mode);
	void SetPosition(Vector3 v);
	
	Matrix4x4 Projection() const;
	Matrix4x4 Orthographic() const;
	Matrix4x4 View(double currentTime);
	
	Matrix4x4 Orbit(double currentTime);
	Matrix4x4 ForcedLook();

	Vector3 GetPosition() { return this->transform.GetPosition(); }
	Vector3 GetFront() { return this->transform.GetOrientation(); }

	void Translate(CameraDirection direction, float deltaTime, bool sprint);
	void Rotate(double x, double y);
	void UpdateOrientation();
	void Zoom(float amount);
};

