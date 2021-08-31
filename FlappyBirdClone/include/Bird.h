#pragma once

#include<iostream>

#include"Entity.h"
#include"Vector.h"


class Bird : public Entity
{
private:
	float maxVelocity = 1.5f;
	Vector gravity; //0.009f
	Vector velocity;
public:
	Bird(Vector p_pos, SDL_Texture* p_texture);
	void Update();
	void Fly();
};