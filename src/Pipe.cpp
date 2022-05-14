#include"Pipe.h"

Pipe::Pipe(Vector p_pos, SDL_Texture* p_tex)
	:Entity(p_pos, p_tex)
{}

void Pipe::Update()
{
	SetPosition(Vector(GetPosition().GetX() - 0.32f, GetPosition().GetY()));

	if (GetPosition().GetX() <= -40)
	{
		SetPosition(Vector(240, GetPosition().GetY()));
		pipeCrossed = true;
	}
}