#pragma once

#include <iostream>
#include "CMath.h"
#include <cassert>
#include <cmath>
#include <cstring>

class Vector3
{
public:
	
	float X;
	float Y;
	float Z;

	Vector3()											 : X(0.0f), Y(0.0f), Z(0.0f) {}
	Vector3(const float x, const float y, const float z) : X(x), Y(y), Z(z)	{}
	explicit Vector3(const float v)						 : X(v), Y(v), Z(v) {}
	 
	const float& operator[](const int i) const { return i == 0 ? this->X : i == 1 ? this->Y : this->Z; }
	float&       operator[](const int i)       { return i == 0 ? this->X : i == 1 ? this->Y : this->Z; }


	float Dot(const Vector3& v)		const;
	Vector3 Cross(const Vector3& v) const;
	Vector3 Reflect(Vector3 n)		const;
	static Vector3 Lerp(Vector3& start, Vector3& end, float& percent);
	static Vector3 Clamp(const Vector3& v, Vector3 min, Vector3 max);
	static Vector3 Saturate(const Vector3& v);
	
	float Distance(Vector3 v) const;

	float Length() const;
	bool IsZero()  const;

	Vector3& Normalized();
	void Normalize();

	void Print(const char* headline = "") const;

	Vector3 operator -() const;

	Vector3& operator /=(const float& v);
	Vector3  operator / (const float& v) const;

	Vector3& operator +=(const Vector3& v);
	Vector3  operator + (const Vector3& v) const;
	Vector3  operator - (const Vector3& v) const;

	Vector3  operator -=(const Vector3& v) const;
	Vector3  operator - (const float& v) const;
	
	Vector3& operator *=(const Vector3& v);
	Vector3  operator * (const Vector3& v) const;
	Vector3& operator *=(const float& v);
	Vector3  operator * (const float& v) const;

	static Vector3 Zero()    { return Vector3( 0,  0,  0); }
	
	static Vector3 Up()      { return Vector3( 0,  1,  0); }
	static Vector3 Down()    { return Vector3( 0, -1,  0); }
	static Vector3 Forward() { return Vector3( 0,  0, -1); }
	static Vector3 Right()   { return Vector3( 1,  0,  0); }
	static Vector3 Left()    { return Vector3(-1,  0,  0); }
	
	~Vector3() = default;
};

inline bool Vector3::IsZero() const
{
	return Length() == 0;
}

inline float Vector3::Dot(const Vector3& v) const
{
	return X * v.X + Y * v.Y + Z * v.Z;
}

inline Vector3 Vector3::Cross(const Vector3& v) const
{
	const float x = Y * v.Z - Z * v.Y;
	const float y = Z * v.X - X * v.Z;
	const float z = X * v.Y - Y * v.X;
	return { x, y, z };
}

inline Vector3 Vector3::Lerp(Vector3& start, Vector3& end, float& percent)
{
	return start + (end - start) * percent;
}

inline Vector3 Vector3::Clamp(const Vector3& v, const Vector3 min, const Vector3 max)
{
	const float x = CMath::Clamp(v.X, min.X, max.X);
	const float y = CMath::Clamp(v.Y, min.Y, max.Y);
	const float z = CMath::Clamp(v.Z, min.Z, max.Z);
	return {x, y, z};
}

inline Vector3 Vector3::Saturate(const Vector3& v)
{
	return Clamp(v, Vector3(0.0f), Vector3(1.0f));
}

inline Vector3 Vector3::Reflect(const Vector3 n) const
{
	return *this - n * this->Dot(n) * 2;
}

inline float Vector3::Distance(const Vector3 v) const
{
	return sqrt( (X - v.X) * (X - v.X) + (Y - v.Y) * (Y - v.Y) + (Z - v.Z) * (Z - v.Z) );
}

inline float Vector3::Length() const
{
	return sqrt(Dot(*this));
}

inline Vector3& Vector3::Normalized()
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

inline void Vector3::Normalize()
{
	*this = Normalized();
}

inline void Vector3::Print(const char* headline) const
{
	if (strlen(headline) != 0)
		std::cout << headline << " | ";
	
	std::cout << "X: " << X << " | Y: " << Y << " | Z: " << Z << "\n";
}

inline Vector3& Vector3::operator/=(const float& v) 
{
	const float m = 1.0f / v;
	this->X *= m;
	this->Y *= m;
	this->Z *= m;
	return *this;
}

inline Vector3 Vector3::operator/(const float& v) const
{
	const float x = X / v;
	const float y = Y / v;
	const float z = Z / v;
	return { x, y, z };
}

inline Vector3& Vector3::operator+=(const Vector3& v)
{
	this->X += v.X;
	this->Y += v.Y;
	this->Z += v.Z;
	return *this;
}

inline Vector3 Vector3::operator+(const Vector3& v) const
{
	const float x = X + v.X;
	const float y = Y + v.Y;
	const float z = Z + v.Z;
	return { x, y, z };
}

inline Vector3 Vector3::operator-() const
{
	return { -X, -Y, -Z };
}

inline Vector3 Vector3::operator-=(const Vector3& v) const
{
	const float x = X - v.X;
	const float y = Y - v.Y;
	const float z = Z - v.Z;
	return { x, y, z };
}

inline Vector3 Vector3::operator-(const Vector3& v) const
{
	const float x = X - v.X;
	const float y = Y - v.Y;
	const float z = Z - v.Z;
	return { x, y, z };
}

inline Vector3 Vector3::operator-(const float& v) const
{
	const float x = X - v;
	const float y = Y - v;
	const float z = Z - v;
	return { x, y, z };
}

inline Vector3& Vector3::operator*=(const Vector3& v)
{
	this->X *= v.X;
	this->Y *= v.Y;
	this->Z *= v.Z;
	return *this;
}

inline Vector3 Vector3::operator*(const Vector3& v) const
{
	const float x = X * v.X;
	const float y = Y * v.Y;
	const float z = Z * v.Z;
	return { x, y, z };
}

inline Vector3& Vector3::operator*=(const float& v)
{
	this->X *= v;
	this->Y *= v;
	this->Z *= v;
	return *this;
}

inline Vector3 Vector3::operator*(const float& v) const
{
	const float x = X * v;
	const float y = Y * v;
	const float z = Z * v;
	return { x, y, z };
}
