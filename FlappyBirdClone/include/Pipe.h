#pragma once

#include<SDL.h>

#include"Entity.h"
#include"Vector.h"

class Pipe : public Entity
{
public:
	bool pipeCrossed = false;

public:
	Pipe(Vector p_pos, SDL_Texture* p_tex);
	void Update();
};