#pragma once

#include<iostream>

#include"Entity.h"
#include"Vector.h"


class Bird : public Entity
{
private:
	float maxVelocity = 1.5f;
	Vector gravity;
	Vector velocity;
	float angle = 0.0f;
	bool fly = false;
	float waveValue = 0.f;

public:
	Bird(Vector p_pos, SDL_Texture* p_texture);
	void Update();
	void Fly();
	float GetAngle();
	void SetAngle(float value);
	void SetGravity(float x, float y);
	void Wave();
};