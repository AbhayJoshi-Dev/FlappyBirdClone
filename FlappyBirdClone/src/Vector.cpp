// sin = Opposite side to O/ Hypotenuse
// cos = Adjacent side / Hypotenuse
// tan = Opposite side / Adjacent side

// degrees = (radians * 180) / pi

#include<math.h>

#include"Vector.h"


Vector::Vector()
	:x(0.0f), y(0.0f)
{}

Vector::Vector(float p_x, float p_y)
	:x(p_x), y(p_y)
{}

void Vector::SetX(float value)
{
	x = value;
}

void Vector::SetY(float value)
{
	y = value;
}

float Vector::GetX()
{
	return x;
}

float Vector::GetY()
{
	return y;
}

void Vector::SetAngle(float angle)
{
	float length = GetLength();
	x = cos(angle) * length;
	y = sin(angle) * length;
}

float Vector::GetAngle()
{
	return atan2(y, x);
}

void Vector::SetLength(float len)
{
	float angle = GetAngle();
	x = cos(angle) * len;
	y = sin(angle) * len;
}

float Vector::GetLength()
{
	return sqrt((double)x * x + (double)y * y);
}

void Vector::AddTo(Vector v)
{
	x += v.x;
	y += v.y;
}

void Vector::SubTo(Vector v)
{
	x -= v.x;
	y -= v.y;
}

void Vector::MulTo(float val)
{
	x *= val;
	y *= val;
}

void Vector::DivTo(float val)
{
	x /= val;
	y /= val;
}