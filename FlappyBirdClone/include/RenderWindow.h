#pragma once

#include<SDL.h>
#include<SDL_image.h>

#include"Entity.h"

class RenderWindow
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	const int multiplier = 3;
public:
	void CreateWindow(const char* p_title, float p_w, float p_h);
	SDL_Texture* LoadTexture(const char* p_filepath);
	int GetRefreshRate();
	void Render(Entity& entity);
	void Render(SDL_Texture* p_tex, Vector p_pos);
	void Render(Entity& p_entity, Vector p_pos);
	void Display();
	void Clear();
	void CleanUp();
};