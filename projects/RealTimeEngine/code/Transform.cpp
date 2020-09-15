// Copyright © 2020  Philip Lindh 
// All rights reserved

#include "Transform.h"

void Transform::SetPosition(Vector3 position)
{
	this->translation = Matrix4x4::CreateTranslation(position);
}

void Transform::SetRotation(Matrix4x4& rotation)
{
	this->rotation = rotation;
}

void Transform::RotateY(const float& angle)
{
	this->rotation.RotateY(angle);
}

void Transform::RotateX(const float& angle)
{
	this->rotation.RotateX(angle);
}

void Transform::RotateZ(const float& angle)
{
	this->rotation.RotateZ(angle);
}

void Transform::SetScale(Matrix4x4& scale)
{
	this->scale = scale;
}

void Transform::SetScale(float& scale)
{
	this->scale.SetScale(scale);
}

void Transform::Translate(Vector3 position)
{
	this->translation.Translate(position);
}

Vector3 Transform::GetPosition() 
{
	return this->translation.GetPosition();
}

Vector3 Transform::GetOrientation()
{
	return { rotation(0, 0), rotation(0, 1), rotation(0, 2) };
}

Matrix4x4& Transform::GetTranslation()
{
	return this->translation;
}

Matrix4x4& Transform::GetRotation()
{
	return this->rotation;
}

Matrix4x4& Transform::GetScale()
{
	return this->scale;
}

Matrix4x4 Transform::Transformation()
{
	return rotation * scale * translation;
}
