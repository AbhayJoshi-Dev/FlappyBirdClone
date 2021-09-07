#pragma once

#include"Entity.h"

class Button : public Entity
{
public:
	Button(Vector pos, SDL_Texture* tex);
	void isClicked();
};