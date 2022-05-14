#include"Entity.h"

Entity::Entity(Vector p_pos, SDL_Texture* p_tex)
	:pos(p_pos), texture(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &currentFrame.w, &currentFrame.h);
}

Vector& Entity::GetPosition()
{
	return pos;
}

void Entity::SetPosition(Vector p_pos)
{
	pos = p_pos;
}

SDL_Texture* Entity::GetTexture()
{
	return texture;
}

SDL_Rect Entity::GetCurrentFrame()
{
	return currentFrame;
}