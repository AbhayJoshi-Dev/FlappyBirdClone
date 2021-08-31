#pragma once

class Vector
{
private:
	float x, y;
public:
	Vector();
	Vector(float p_x, float p_y);
	void SetX(float value);
	void SetY(float value);
	float GetX();
	float GetY();
	void SetAngle(float angle);
	float GetAngle();
	void SetLength(float len);
	float GetLength();
	void AddTo(Vector v);
	void SubTo(Vector v);
	void MulTo(float val);
	void DivTo(float val);
};