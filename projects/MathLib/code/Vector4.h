// Copyright © 2020  Philip Lindh 
// All rights reserved

#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include <cmath>
#include <cstring>

class Vector4 
{
public:
	
	float X;
	float Y;
	float Z;
	float W;

	Vector4() : X(0.0f), Y(0.0f), Z(0.0f), W(1.0f) {}
	Vector4(const float x, const float y, const float z, const float w) : X(x), Y(y), Z(z), W(w)			 {}
	Vector4(const float x, const float y, const float z)				: X(0.0f), Y(0.0f), Z(0.0f), W(1.0f) {}

	const float& operator[](const int i) const { return i == 0 ? this->X : i == 1 ? this->Y : i == 2 ? this->Z : this->W; }
	float&       operator[](const int i)       { return i == 0 ? this->X : i == 1 ? this->Y : i == 2 ? this->Z : this->W; }
	
	void Print(const char* headline = "") const;
	
	Vector3 To3D() const;
	Vector2 To2D() const;

	float Dot(const Vector4& v)		const;
	float Dot4(const Vector4& v)	const;
	Vector4 Cross(const Vector4& v) const;

	Vector4& Normalized();
	void Normalize();

	float Length() const;
	bool  IsZero() const;

	Vector4 operator / (const float& v) const;
	
	Vector4 operator * (const float& v) const;
	Vector4 operator * (const Vector4& v) const;
	Vector4 operator * (const Vector3& v) const;

	Vector4 operator + (const Vector4& v) const;
	
	Vector4 operator - (const Vector4& v) const;
	Vector4 operator -() const;

	~Vector4() = default;
};

inline void Vector4::Print(const char* headline) const
{
	if (strlen(headline) != 0)
		std::cout << headline << " | ";

	std::cout << "X: " << X << " | Y: " << Y << " | Z: " << Z << " | W: " << W << "\n";
}

inline Vector3 Vector4::To3D() const
{
	return { X, Y, Z };
}

inline Vector2 Vector4::To2D() const
{
	return { X, Y };
}

inline float Vector4::Dot(const Vector4& v) const
{
	return this->X * v.X + this->Y * v.Y + this->Z * v.Z;
}

inline float Vector4::Dot4(const Vector4& v) const
{
	return this->X * v.X + this->Y * v.Y + this->Z * v.Z + this->W * v.W;
}

inline Vector4 Vector4::Cross(const Vector4& v) const
{
	const float x = Y * v.Z - Z * v.Y;
	const float y = Z * v.X - X * v.Z;
	const float z = X * v.Y - Y * v.X;
	return { x, y, z, 1.0 };
}

inline Vector4& Vector4::Normalized()
{
	const float length = Length();
	if (length > 1e-05)
	{
		const float factor = 1.0f / length;
		this->X *= factor;
		this->Y *= factor;
		this->Z *= factor;
	}
	return *this;
}

inline void Vector4::Normalize()
{
	*this = Normalized();
}

inline float Vector4::Length() const
{
	return sqrt(Dot(*this));
}

inline bool Vector4::IsZero() const
{
	return Length() == 0;
}

inline Vector4 Vector4::operator*(const Vector4& v) const
{
	const float x = X * v.X;
	const float y = Y * v.Y;
	const float z = Z * v.Z;
	return { x, y, z, 1.0 };
}

inline Vector4 Vector4::operator*(const Vector3& v) const
{
	const float x = X * v.X;
	const float y = Y * v.Y;
	const float z = Z * v.Z;
	return { x, y, z, 1.0 };
}

inline Vector4 Vector4::operator*(const float& v) const
{
	const float x = X * v;
	const float y = Y * v;
	const float z = Z * v;
	return { x, y, z, 1.0 };
}

inline Vector4 Vector4::operator-() const
{
	return { -X, -Y, -Z, -W };
}

inline Vector4 Vector4::operator/(const float& v) const
{
	const float inv = 1.0f / v;
	const float x = X * inv;
	const float y = Y * inv;
	const float z = Z * inv;
	return { x, y, z, 1.0 };
}

inline Vector4 Vector4::operator+(const Vector4& v) const
{
	const float x = X + v.X;
	const float y = Y + v.Y;
	const float z = Z + v.Z;
	return { x, y, z, 1.0 };
}

inline Vector4 Vector4::operator-(const Vector4& v) const
{
	const float x = X - v.X;
	const float y = Y - v.Y;
	const float z = Z - v.Z;
	return { x, y, z, 1.0 };
}