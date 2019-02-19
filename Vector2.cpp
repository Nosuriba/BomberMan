#include "Vector2.h"


Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}

Vector2::Vector2(unsigned int x, unsigned int y)
{
	this->x = x;
	this->y = y;
}

Vector2::~Vector2()
{
}

Vector2 & Vector2::operator=(const Vector2 & vec)
{
	this->x = vec.x;
	this->y = vec.y;

	return *this;
}

int Vector2::operator[](int j)
{
	if (j == 0)
	{
		return this->x;
	}
	else if (j == 1)
	{
		return this->y;
	}
	else
	{
		return this->x;
	}
}

bool Vector2::operator==(const Vector2 & vec) const
{
	return ((this->x == vec.x) && (this->y == vec.y));
}

bool Vector2::operator!=(const Vector2 & vec) const
{
	return !((this->x == vec.x) && (this->y == vec.y));
}

bool Vector2::operator>(const Vector2 & vec) const
{
	return ((this->x > vec.x) && (this->y > vec.y));
}

bool Vector2::operator<(const Vector2 & vec) const
{
	return ((this->x < vec.x) && (this->y < vec.y));
}

bool Vector2::operator>=(const Vector2 & vec) const
{
	return ((this->x >= vec.x) && (this->y >= vec.y));
}

bool Vector2::operator<=(const Vector2 & vec) const
{
	return ((this->x <= vec.x) && (this->y <= vec.y));
}

Vector2 & Vector2::operator+=(const Vector2 & vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2 & Vector2::operator-=(const Vector2 & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2 & Vector2::operator*=(int k)
{
	this->x *= k;
	this->y *= k;

	return *this;
}

Vector2 & Vector2::operator/=(int k)
{
	this->x /= k;
	this->y /= k;

	return *this;
}

Vector2 Vector2::operator+() const
{
	return *this;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-this->x, -this->y);
}

Vector2 operator+(const Vector2 & i, const Vector2 & j)
{
	Vector2 vec;
	vec.x = i.x + j.x;
	vec.y = i.y + j.y;

	return vec;
}

Vector2 operator+(const Vector2 & i, int j)
{
	Vector2 vec;
	vec.x = i.x + j;
	vec.y = i.y + j;

	return vec;
}

Vector2 operator-(const Vector2 & i, const Vector2 & j)
{
	Vector2 vec;

	vec.x = i.x - j.x;
	vec.y = i.y - j.y;

	return vec;
}

Vector2 operator-(const Vector2 & i, int j)
{
	Vector2 vec;

	vec.x = i.x - j;
	vec.y = i.y - j;

	return vec;
}

Vector2 operator*(const Vector2 & i, int k)
{
	Vector2 vec;

	vec.x = i.x * k;
	vec.y = i.y * k;

	return vec;
}

Vector2 operator*(int k, const Vector2 & i)
{
	Vector2 vec;

	vec.x = k * i.x;
	vec.y = k * i.y;

	return vec;
}

Vector2 operator/(const Vector2 & i, int k)
{
	Vector2 vec;

	vec.x = i.x / k;
	vec.y = i.y / k;


	return vec;
}
