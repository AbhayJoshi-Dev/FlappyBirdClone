#include"Bird.h"

Bird::Bird(Vector p_pos, SDL_Texture* p_texture)
	:Entity(p_pos, p_texture)
{
	gravity.SetX(0.0f);
	gravity.SetY(0.04f);//0.009
}

void Bird::Update()
{
	if (velocity.GetY() <= 1.2)
		velocity.AddTo(gravity);

	if (velocity.GetY() > 1.2)
		velocity.SetY(1.2);

	SetPosition(Vector(25, GetPosition().GetY() + velocity.GetY()));


	if (velocity.GetY() >= 1.0f && angle <= 450.0f)
	{
		fly = false;
		angle += 3.0f;
		if (angle <= 0.0f)
			angle = 0.0f;
	}

	if (velocity.GetY() < 0.0f)
	{
		fly = true;
		angle = 330;
	}

}

void Bird::Fly()
{
	if (velocity.GetY() >= -1.5)
		velocity.SetY(-1.5);

	if (velocity.GetY() < -1.5)
		velocity.SetY(-1.5);
}

float Bird::GetAngle()
{
	return angle;
}