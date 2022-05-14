#include"Ground.h"

Ground::Ground(Vector p_pos, SDL_Texture* p_tex)
	:Entity(p_pos, p_tex)
{}

void Ground::Update()
{
	SetPosition(Vector(GetPosition().GetX() - 0.32f, 200.0f));

	if (GetPosition().GetX() <= -154)
	{
		SetPosition(Vector(154, 200));
	}

}