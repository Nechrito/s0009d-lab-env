// Copyright © 2020  Philip Lindh 
// All rights reserved

#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"

class Transform
{
private:
	
	Matrix4x4 transformation;
	Matrix4x4 translation;
	Matrix4x4 rotation;
	Matrix4x4 scale;

	Vector3 zAxis;
	Vector3 xAxis;
	Vector3 yAxis;
	
public:
	
	Transform() = default;

	void SetPosition(Vector3 position);
	void SetRotation(Matrix4x4& rotation);
	void RotateY(const float& angle);
	void RotateX(const float& angle);
	void RotateZ(const float& angle);

	void SetScale(Matrix4x4& scale);
	void SetScale(float& scale);
	
	void Translate(Vector3 position);

	Vector3 GetPosition();
	Vector3 GetOrientation();
	
	Matrix4x4& GetTranslation();
	Matrix4x4& GetRotation();
	Matrix4x4& GetScale();
	Matrix4x4 Transformation();
	
	~Transform() = default;
};

