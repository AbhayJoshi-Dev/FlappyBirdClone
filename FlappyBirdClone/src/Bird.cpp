#include"Bird.h"

Bird::Bird(Vector p_pos, SDL_Texture* p_texture)
	:Entity(p_pos, p_texture)
{
	gravity.SetX(0.0f);
	gravity.SetY(0.02f);//0.009
}

void Bird::Update()
{
	if (velocity.GetY() <= .8)
		velocity.AddTo(gravity);

	if (velocity.GetY() > .8)
		velocity.SetY(.8);

	SetPosition(Vector(25, GetPosition().GetY() + velocity.GetY()));
}

void Bird::Fly()
{
	if (velocity.GetY() >= -.8)
		velocity.SetY(-0.85);

	if (velocity.GetY() < -.8)
		velocity.SetY(-.8);
}