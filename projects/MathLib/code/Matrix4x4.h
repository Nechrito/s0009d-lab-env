// Copyright © 2020  Philip Lindh 
// All rights reserved

#pragma once

#include "Vector4.h"
#include "Vector3.h"

const float DEG2RAD = 3.141593f / 180.0f;
const float RAD2DEG = 180.0f / 3.141593f;
const float EPSILON = 0.00001f;

class Matrix4x4
{
private:
	
	float mat[4][4];
	
public:

	Matrix4x4() { *this = Identity(); }

	Matrix4x4(float a00, float a01, float a02, float a03,
	          float a10, float a11, float a12, float a13,
	          float a20, float a21, float a22, float a23,
	          float a30, float a31, float a32, float a33);

	Matrix4x4(Vector4& v1, Vector4& v2, Vector4& v3, Vector4& v4);

	static Matrix4x4 Identity();

	Matrix4x4& operator=(const Matrix4x4& m);
	
	void	  operator*= (const Matrix4x4& m);
	Matrix4x4 operator * (float& m) const;
	Matrix4x4 operator * (const Matrix4x4& m);
	Vector4	  operator * (const Vector4& v) const;
	
	Vector4	operator()(int col) const;
	float& operator()(int row, int col);
	float  operator()(int row, int col) const;
	
	const float* Ptr() const;
	
	void Print(const char* headline = "");

	static Matrix4x4 CreateLookAt(Vector3 src, Vector3& dst, Vector3& up);
	static Matrix4x4 CreateProjection(float angle, float aspect, float near, float far);
	static Matrix4x4 OrthogonalProjection(float left, float right, float bottom, float top, float near, float far);
	static Matrix4x4 Viewport(int x, int y, int width, int height, int resolution);
	
	void Translate(Vector3& v);
	void Translate(float& x, float& y, float& z);

	void SetScale(float scale);

	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);

	Vector3 GetPosition();

	Matrix4x4 Transpose();
	
	static Matrix4x4 CreateTranslation(Vector3& v);
	static Matrix4x4 CreateTranslation(float x, float y, float z);

	static Matrix4x4 CreateScale(float scale);
	static Matrix4x4 CreateScale(float x, float y, float z);
	

};

inline Matrix4x4 Matrix4x4::Identity()
{
	return
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
}

inline Matrix4x4::Matrix4x4
(const float a00, const float a01, const float a02, const float a03,
 const float a10, const float a11, const float a12, const float a13,
 const float a20, const float a21, const float a22, const float a23,
 const float a30, const float a31, const float a32, const float a33)
{
	(*this)(0, 0) = a00;
	(*this)(0, 1) = a01;
	(*this)(0, 2) = a02;
	(*this)(0, 3) = a03;

	(*this)(1, 0) = a10;
	(*this)(1, 1) = a11;
	(*this)(1, 2) = a12;
	(*this)(1, 3) = a13;

	(*this)(2, 0) = a20;
	(*this)(2, 1) = a21;
	(*this)(2, 2) = a22;
	(*this)(2, 3) = a23;

	(*this)(3, 0) = a30;
	(*this)(3, 1) = a31;
	(*this)(3, 2) = a32;
	(*this)(3, 3) = a33;
}

inline Matrix4x4::Matrix4x4(Vector4& v1, Vector4& v2, Vector4& v3, Vector4& v4)
{
	(*this)(0) = v1;
	(*this)(1) = v2;
	(*this)(2) = v3;
	(*this)(3) = v4;
}

inline Matrix4x4& Matrix4x4::operator=(const Matrix4x4& m)
{
	(*this)(0, 0) = m(0, 0);
	(*this)(0, 1) = m(0, 1);
	(*this)(0, 2) = m(0, 2);
	(*this)(0, 3) = m(0, 3);

	(*this)(1, 0) = m(1, 0);
	(*this)(1, 1) = m(1, 1);
	(*this)(1, 2) = m(1, 2);
	(*this)(1, 3) = m(1, 3);

	(*this)(2, 0) = m(2, 0);
	(*this)(2, 1) = m(2, 1);
	(*this)(2, 2) = m(2, 2);
	(*this)(2, 3) = m(2, 3);

	(*this)(3, 0) = m(3, 0);
	(*this)(3, 1) = m(3, 1);
	(*this)(3, 2) = m(3, 2);
	(*this)(3, 3) = m(3, 3);

	return *this;
}

inline const float* Matrix4x4::Ptr() const
{
	return &mat[0][0];
}

inline void Matrix4x4::Print(const char* headline)
{
	std::cout << headline << std::endl;
	for (auto& row : mat)
	{
		for (float col : row)
		{
			std::cout << col << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

inline Matrix4x4 Matrix4x4::CreateLookAt(const Vector3 src, Vector3& dst, Vector3& up)
{
	const Vector3 zAxis = (src - dst).Normalized();
	const Vector3 xAxis = up.Normalized().Cross(zAxis).Normalized();
	const Vector3 yAxis = zAxis.Cross(xAxis);
	
	return
	{
		xAxis.X, xAxis.Y, xAxis.Z, -xAxis.Dot(src),
		yAxis.X, yAxis.Y, yAxis.Z, -yAxis.Dot(src),
        zAxis.X, zAxis.Y, zAxis.Z, -zAxis.Dot(src),
		0, 0, 0, 1
	};
}

inline Matrix4x4 Matrix4x4::CreateProjection(const float angle, const float aspect, const float near, const float far)
{
	const float t = tanf(angle / 2 * DEG2RAD) * near;
	const float l = -t * aspect;
	const float r = t * aspect;
	const float b = l;
	
	return
	{
		2 * near / (r - l), 0, (r + l) / (r - l),  0,
		0, 2 * near / (t - b), (t + b) / (t - b),  0,
		0, 0, (-far + near) / (far - near), -2 * far * near / (far - near),
		0, 0, -1, 0
	};
}

inline Matrix4x4 Matrix4x4::OrthogonalProjection(const float left, const float right, const float bottom, const float top, const float near, const float far)
{
	return
	{
		2/(right-left), 0, 0, -(right+left)/(right-left),
		0, 2/(top-bottom), 0, -(top+bottom)/(top-bottom),
		0, 0, -2/(far-near), -(far+near)/(far-near),
		0, 0, 0, 1
	};
}

inline Matrix4x4 Matrix4x4::Viewport(const int x, const int y, const int width, const int height, const int resolution)
{
	Matrix4x4 m;

	m(0, 3) = x + width / 2.0f;
	m(1, 3) = y + height / 2.0f;
	m(2, 3) = resolution / 2.0f;

	m(0, 0) = width / 2.0f;
	m(1, 1) = height / 2.0f;
	m(2, 2) = resolution / 2.0f;

	return m;
}

inline void Matrix4x4::Translate(Vector3& v)
{
	this->Translate(v.X, v.Y, v.Z);
}

inline void Matrix4x4::Translate(float& x, float& y, float& z)
{
	(*this)(0, 3) += x;
	(*this)(1, 3) += y;
	(*this)(2, 3) += z;
}

inline Matrix4x4 Matrix4x4::CreateTranslation(Vector3& v)
{
	return CreateTranslation(v.X, v.Y, v.Z);
}

inline Matrix4x4 Matrix4x4::CreateTranslation(const float x, const float y, const float z)
{
	return
	{
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};
}

inline Matrix4x4 Matrix4x4::CreateScale(const float scale)
{
	return CreateScale(scale, scale, scale);
}

inline void Matrix4x4::SetScale(const float scale)
{
	*this *= CreateScale(scale, scale, scale);
}

inline Matrix4x4 Matrix4x4::CreateScale(const float x, const float y, const float z)
{
	return
	{
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	};
}

inline void Matrix4x4::RotateX(float angle)
{
	angle *= DEG2RAD;

	Matrix4x4 rotated(1, 0, 0, 0,
	                  0, cosf(angle), -sinf(-angle), 0,
	                  0, sinf(-angle), cosf(angle), 0,
	                  0, 0, 0, 1);
	*this *= rotated;
}

inline void Matrix4x4::RotateY(float angle)
{
	angle *= DEG2RAD;
	
	Matrix4x4 rotated(cosf(angle), 0, -sinf(angle), 0,
	                  0, 1, 0, 0,
	                 -sinf(-angle), 0, cosf(angle), 0,
	                  0, 0, 0, 1);
	*this *= rotated;
}

inline void Matrix4x4::RotateZ(float angle)
{
	angle *= DEG2RAD;

	Matrix4x4 rotated(cosf(angle), -sinf(-angle), 0, 0,
	                  sinf(-angle), cosf(angle), 0, 0,
	                  0, 0, 1, 0,
	                  0, 0, 0, 1);
	*this *= rotated;
}

inline Vector3 Matrix4x4::GetPosition()
{
	const float x = (*this)(0, 3);
	const float y = (*this)(1, 3);
	const float z = (*this)(2, 3);
	return { x, y, z };
}
	
inline Matrix4x4 Matrix4x4::Transpose()
{
	Matrix4x4 trans;

	for (auto i = 0; i < 4; ++i)
	{
		for (auto j = 0; j < 4; ++j)
		{
			trans.mat[i][j] = (*this)(j, i);
		}
	}
	
	return trans;
}

inline void Matrix4x4::operator*=(const Matrix4x4& m)
{
	*this = *this * m;
}

inline Matrix4x4 Matrix4x4::operator*(const Matrix4x4& m)
{
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result(i, j) = 0;
			
			for (int k = 0; k < 4; ++k)
			{
				result(i, j) += (*this)(i, k) * m(k, j);
			}
		}
	}
	
	return result;
}

inline Matrix4x4 Matrix4x4::operator*(float& m) const
{
	Matrix4x4 copy = *this;
	
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			copy(i, j) *= m;
		}
	}
	
	return copy;
}

inline Vector4 Matrix4x4::operator()(const int col) const
{
	return
	{
		(*this)(0, col),
	    (*this)(1, col),
	    (*this)(2, col),
	    (*this)(3, col)
	};
}

inline Vector4 Matrix4x4::operator*(const Vector4& v) const
{
	const float x = v.Dot4((*this)(0));
	const float y = v.Dot4((*this)(1));
	const float z = v.Dot4((*this)(2));
	const float w = v.Dot4((*this)(3));

	return {x, y, z, w};
}

inline float& Matrix4x4::operator()(const int row, const int col)
{
	return mat[row][col];
}

inline float Matrix4x4::operator()(const int row, const int col) const
{
	return mat[row][col];
}
