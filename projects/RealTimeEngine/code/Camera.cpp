// Copyright © 2020  Philip Lindh 
// All rights reserved

#include "Camera.h"

Camera::Camera()
{
	this->activeMode = CameraMode::FREELOOK;

	this->target = Vector3::Zero();

	this->CameraX = Vector3::Right();
	this->CameraY = Vector3::Up();
	this->CameraZ = Vector3::Forward();

	// Supposedly overriden elsewhere, these are simply default values
	this->Width = 1280.0f;
	this->Height = 720.0f;

	this->Near = 0.1f;
	this->Far = 1000.0f;
	
	this->currentFov = 65.0f;
	this->maxFov = currentFov;
	
	this->yaw = -90.0f;
	this->pitch = 0.0f;
}

void Camera::SetFieldOfView(const float fov, const float near, const float far)
{
	this->currentFov = fov;
	this->maxFov = fov;

	this->Near = near;
	this->Far = far;
}

void Camera::SetViewport(const int width, const int height)
{
	this->Width = width;
	this->Height = height;
}

void Camera::SetTarget(const Vector3 target)
{
	this->target = target;
}

void Camera::SetCameraMode(const CameraMode mode)
{
	this->activeMode = mode;
}

void Camera::SetPosition(const Vector3 v)
{
	this->transform.SetPosition(v);
}

Matrix4x4 Camera::Projection() const
{
	return Matrix4x4::CreateProjection(currentFov, float(Width) / float(Height), Near, Far);
}

Matrix4x4 Camera::Orthographic() const
{
	return Matrix4x4::OrthogonalProjection(0, float(Width), 0, float(Height), Near, Far);
}

Matrix4x4 Camera::View(const double currentTime)
{
	switch (activeMode)
	{
		case CameraMode::FREELOOK: return transform.Transformation();
		case CameraMode::FORCED:   return ForcedLook();
		case CameraMode::ORBIT:    return Orbit(currentTime);
	}
	
	return Matrix4x4::Identity();
}

Matrix4x4 Camera::Orbit(const double currentTime) 
{
	const float radius = 12.5f;
	const float radiusX = sin(currentTime) * radius + target.X;
	const float radiusZ = cos(currentTime) * radius + target.Z;

	const Vector3 src(radiusX, target.Y - transform.GetPosition().Y, radiusZ);

	return Matrix4x4::CreateLookAt(src, target, CameraY);
}

Matrix4x4 Camera::ForcedLook()
{
	Vector3 src = transform.GetPosition();
	src.Y = target.Y - src.Y;
	return Matrix4x4::CreateLookAt(src, target, CameraY);
}

void Camera::Translate(const CameraDirection direction, const float deltaTime, const bool sprint)
{
	const float velocity = (sprint ? 7.0f : 4.0f) * deltaTime;

	switch (direction)
	{
		case CameraDirection::FORWARD:	transform.Translate( CameraZ * velocity); break;
		case CameraDirection::BACKWARD: transform.Translate(-CameraZ * velocity); break;
		case CameraDirection::LEFT:		transform.Translate(-CameraX * velocity); break;
		case CameraDirection::RIGHT:	transform.Translate( CameraX * velocity); break;
	}
	
	UpdateOrientation();
}

void Camera::Rotate(double x, double y)
{
	x *= 0.1;
	y *= 0.1;

	yaw += x;
	pitch += y;

	transform.RotateY(x);
	//transform.RotateX(y);

	UpdateOrientation();
}

void Camera::Zoom(const float amount)
{
	if (currentFov >= 1.0f && currentFov <= maxFov)
		currentFov -= amount;

	if (currentFov <= 1.0f)
		currentFov =  1.0f;

	if (currentFov >= maxFov)
		currentFov =  maxFov;
}

void Camera::UpdateOrientation()
{
	this->CameraZ = Vector3(cosf(yaw * DEG2RAD), 0, sinf(-yaw * DEG2RAD)).Normalized();
	this->CameraX = CameraZ.Cross(CameraY).Normalized();
	this->CameraY = CameraX.Cross(CameraZ).Normalized();
}