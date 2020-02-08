#pragma once
#include <iostream>
#include <Vec2.h>

float ToDegrees(float radians)
{
	return radians * 57.2958f;
}
float ToRadians(float degrees)
{
	return degrees / 57.2958f;
}
double ToRadians(double degrees)
{
	return degrees / 57.2958;
}
Vec2::Vec2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
Vec2::Vec2()
	{
		x = 0;
		y = 0;
	}
Vec2 Vec2:: operator-()
	{
		Vec2 res;
		res.x = -x;
		res.y = -y;
		return res;
	}
void Vec2:: operator = (float const& obj)
	{
		
		x = obj;
		y = obj;
	}

void Vec2:: operator = (Vec2 const& obj)
	{
		x = obj.x;
		y = obj.y;
	}
Vec2 Vec2:: operator + (float const& obj)
	{
		Vec2 res;
		res.x = x + obj;
		res.y = y + obj;
		return res;
	}

Vec2 Vec2::operator + (Vec2 const& obj)
	{
		Vec2 res;
		res.x = x + obj.x;
		res.y = y + obj.y;
		return res;
	}

Vec2 Vec2:: operator - (float const& obj)
	{
		Vec2 res;
		res.x = x - obj;
		res.y = y - obj;
		return res;
	}

Vec2 Vec2:: operator - (Vec2 const& obj)
	{
		Vec2 res;
		res.x = x - obj.x;
		res.y = y - obj.y;
		return res;
	}
Vec2 Vec2:: operator * (float const& obj)
	{
		Vec2 res;
		res.x = x * obj;
		res.y = y * obj;
		return res;
	}

Vec2 Vec2:: operator * (Vec2 const& obj)
	{
		Vec2 res;
		res.x = x * obj.x;
		res.y = y * obj.y;
		return res;
	}

Vec2 Vec2:: operator / (float const& obj)
	{
		Vec2 res;
		res.x = x / obj;
		res.y = y / obj;
		return res;
	}

Vec2 Vec2:: operator / (Vec2 const& obj)
	{
		Vec2 res;
		res.x = x / obj.x;
		res.y = y / obj.y;
		return res;
	}

float Vec2::Length()
{
	return sqrt(x * x + y * y);
}

Vec2 Vec2:: Normalize()
{
	Vec2 res(x, y);
	const float length = Length();
	return res / length;
}

float Vec2:: Dot(Vec2 const& _v2)
{
	return x * _v2.x + y * _v2.y;
}

float Vec2::Angle(const Vec2& other) const
{
	return ToDegrees(atan2(other.y, other.x) - atan2(y, x));
}
float Vec2::Distance(const Vec2& other) const
{
	return Vec2(x - other.x, y - other.y).Length();
}
Vec2 Vec2::Rotate(const float& degrees) const
{
	Vec2 res;
	float fRadians = ToRadians(degrees);
	res.x = x * cos((double)fRadians) - y * sin((double)fRadians);
	res.y = x * sin((double)fRadians) + y * cos((double)fRadians);
	return res;
}
Vec2 Vec2::Rotate(const double& degrees) const
{
	Vec2 res;
	double dRadians = ToRadians(degrees);
	res.x = x * cos(dRadians) - y * sin(dRadians);
	res.y = x * sin(dRadians) + y * cos(dRadians);
	return res;
}
Vec2 Vec2::Resize(const float& length)
{
	Vec2 res(x, y);
	return Normalize()*length;
}


