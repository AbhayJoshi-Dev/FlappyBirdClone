#pragma once

#include<SDL.h>

#include"Vector.h"

class Entity
{
private:
	Vector pos;
	SDL_Rect currentFrame;
	SDL_Texture* texture;
public:
	Entity(Vector p_pos, SDL_Texture* p_tex);
	Vector& GetPosition();
	void SetPosition(Vector p_pos);
	SDL_Texture* GetTexture();
	SDL_Rect GetCurrentFrame();
};