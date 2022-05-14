#pragma once

class Vector
{
public:
	Vector() = default;
	Vector(float p_x, float p_y);

	// Returns the x component.
	float GetX() const;

	// Sets the x component.
	void SetX(float value);

	// Returns the y component.
	float GetY() const;

	// Sets the x component.
	void SetY(float value);

	// Returns the angle.
	float GetAngle() const;

	// Sets the angle.
	void SetAngle(float angle);

	// Returns the length.
	float GetLength() const;

	// Sets the length.
	void SetLength(float len);

	// Adds given vector to current.
	void AddTo(const Vector &v);

	// Subtracts given vector from current.
	void SubTo(const Vector &v);

	// Scales vector by given factor equally.
	void Scale(float factor);

	// Scales vector by given x and y factors along both components.
	void Scale(float x, float y);

	// Finds the dot product of current and other vector.
	float Dot(const Vector& other) const;

	Vector& Unitize();

	Vector Unit() const;

	// Returns addition of other and current vector.
	Vector operator+(const Vector& other) const;

	// Returns subtraction of other vector and from current vector.
	Vector operator-(const Vector& other) const;

private:
	// Saves us from having a default constructor.
	float x = 0.f;
	float y = 0.f;
};
