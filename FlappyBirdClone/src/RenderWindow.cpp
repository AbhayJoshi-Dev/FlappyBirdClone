#include<iostream>
#include<string>

#include"RenderWindow.h"

void RenderWindow::CreateWindow(const char* p_title, float p_w, float p_h)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)p_w, (int)p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
		std::cout << "Window failed to load. ERROR: " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

}

SDL_Texture* RenderWindow::LoadTexture(const char* p_filepath)
{
	SDL_Texture* tex = NULL;

	tex = IMG_LoadTexture(renderer, p_filepath);

	if (tex == NULL)
		std::cout << "Failed to load texture. ERROR :" << IMG_GetError << std::endl;

	return tex;
}

int RenderWindow::GetRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(window);
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, 0, &mode);

	return mode.refresh_rate;
}

void RenderWindow::Render(Entity& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.GetCurrentFrame().x;
	src.y = p_entity.GetCurrentFrame().y;
	src.w = p_entity.GetCurrentFrame().w;
	src.h = p_entity.GetCurrentFrame().h;

	SDL_Rect dst;
	dst.x = (int)p_entity.GetPosition().GetX() * multiplier;
	dst.y = (int)p_entity.GetPosition().GetY() * multiplier;
	dst.w = (int)p_entity.GetCurrentFrame().w * multiplier;
	dst.h = (int)p_entity.GetCurrentFrame().h * multiplier;

	SDL_RenderCopy(renderer, p_entity.GetTexture(), &src, &dst);
}

void RenderWindow::Render(SDL_Texture* p_tex, Vector p_pos)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = (int)p_pos.GetX() * multiplier;
	dst.y = (int)p_pos.GetY() * multiplier;
	dst.w = (int)src.w * multiplier;
	dst.h = (int)src.h * multiplier;

	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void RenderWindow::Render(Entity& p_entity, Vector p_pos)
{
	SDL_Rect src;
	src.x = p_entity.GetCurrentFrame().x;
	src.y = p_entity.GetCurrentFrame().y;
	src.w = p_entity.GetCurrentFrame().w;
	src.h = p_entity.GetCurrentFrame().h;

	SDL_Rect dst;
	dst.x = (int)p_pos.GetX() * multiplier;
	dst.y = (int)p_pos.GetY() * multiplier;
	dst.w = (int)p_entity.GetCurrentFrame().w * multiplier;
	dst.h = (int)p_entity.GetCurrentFrame().h * multiplier;

	SDL_RenderCopy(renderer, p_entity.GetTexture(), &src, &dst);
}

void RenderWindow::RenderRotate(SDL_Texture* p_tex, Vector p_pos, float angle)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = (int)p_pos.GetX() * multiplier;
	dst.y = (int)p_pos.GetY() * multiplier;
	dst.w = src.w * multiplier;
	dst.h = src.h * multiplier;

	SDL_RenderCopyEx(renderer, p_tex, &src, &dst, angle, NULL, SDL_FLIP_NONE);
}

void RenderWindow::RenderText(float x, float y, int score, TTF_Font* font, SDL_Color colour)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, std::to_string(score).c_str(), colour);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = surfaceMessage->w;
	src.h = surfaceMessage->h;

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, message, &src, &dst);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

void RenderWindow::Display()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::Clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::CleanUp()
{
	SDL_DestroyWindow(window);
}