#pragma once
#include <iostream>
#include "CMath.h"
#include <cassert>
#include <cmath>
#include <cstring>

class Vector2
{
public:
	float X;
	float Y;

	Vector2() : X(0), Y(0) { }
	Vector2(const float val) : X(val), Y(val) { }
	Vector2(const float x, const float y) : X(x), Y(y) { }

	const float& operator[](const int i) const { return i == 0 ? this->X : this->Y; }
	float& operator[](const int i) { return i == 0 ? this->X : this->Y; }
	
	static Vector2 Lerp(Vector2& start, Vector2& end, float& percent);
	static Vector2 Clamp(const Vector2& v, Vector2 min, Vector2 max);
	static Vector2 Saturate(const Vector2& v);
	
	static float Distance(Vector2& first, Vector2& second);
	float Length() const;

	Vector2& Normalized();
	void Normalize();

	float IsZero() const;

	void Print(const char* headline = "") const;

	Vector2& operator +=(const Vector2& v);
	Vector2& operator + (const Vector2& v);

	Vector2& operator -=(const Vector2& v);
	Vector2& operator - (const Vector2& v);

	Vector2& operator *=(const Vector2& v);
	Vector2& operator *=(const float& v);
	Vector2& operator * (const float& v);
};

inline Vector2 Vector2::Lerp(Vector2& start, Vector2& end, float& percent)
{
	return start + (end - start) * percent;
}

inline Vector2 Vector2::Clamp(const Vector2& v, Vector2 min, Vector2 max)
{
	const float x = CMath::Clamp(v.X, min.X, max.X);
	const float y = CMath::Clamp(v.Y, min.Y, max.Y);
	return { x, y };
}

inline Vector2 Vector2::Saturate(const Vector2& v)
{
	return Clamp(v, Vector2(0, 0), Vector2(0, 0));
}

inline float Vector2::Distance(Vector2& first, Vector2& second)
{
	const Vector2 distance = first - second;
	return distance.Length();
}

inline float Vector2::Length() const
{
	return sqrt(X * X + Y * Y);
}

inline Vector2& Vector2::Normalized() 
{
	const float length = Length();
	if (length > 1e-05)
	{
		const float factor = 1.0f / length;
		this->X *= factor;
		this->Y *= factor;
	}
	return *this;
}

inline void Vector2::Normalize()
{
	*this = Normalized();
}

inline float Vector2::IsZero() const
{
	return X == 0 && Y == 0;
}

inline void Vector2::Print(const char* headline) const
{
	if (strlen(headline) != 0)
		std::cout << headline << " | ";

	std::cout << "X: " << X << " | Y: " << Y << "\n";
}

inline Vector2& Vector2::operator+=(const Vector2& v)
{
	X += v.X;
	Y += v.Y;
	return *this;
}

inline Vector2& Vector2::operator+(const Vector2& v)
{
	X += v.X;
	Y += v.Y;
	return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& v)
{
	X -= v.X;
	Y -= v.Y;
	return *this;
}

inline Vector2& Vector2::operator-(const Vector2& v)
{
	X -= v.X;
	Y -= v.Y;
	return *this;
}

inline Vector2& Vector2::operator*=(const Vector2& v)
{
	X *= v.X;
	Y *= v.Y;
	return *this;
}

inline Vector2& Vector2::operator*=(const float& v)
{
	X *= v;
	Y *= v;
	return *this;
}

inline Vector2& Vector2::operator*(const float& v)
{
	X *= v;
	Y *= v;
	return *this;
}