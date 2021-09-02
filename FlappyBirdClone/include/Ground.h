#pragma once

#include"Entity.h"

class Ground : public Entity
{
public:
	Ground(Vector p_pos, SDL_Texture* p_tex);
	void Update();
};