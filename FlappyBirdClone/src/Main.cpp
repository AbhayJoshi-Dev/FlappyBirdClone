// sin	Opposite side to O/ Hypotenuse
// cos	Adjacent side / Hypotenuse
// tan	Opposite side / Adjacent side

// degrees = (radians * 180) / pi

#include<SDL.h>
#include<iostream>
#include<SDL_image.h>
#include<stdlib.h>
#include<time.h>

#include"RenderWindow.h"
#include"Entity.h"
#include"Pipe.h"
#include"Utils.h"
#include"Bird.h"
#include"Ground.h"

RenderWindow window;

const int SCREEN_WIDTH = 432;
const int SCREEN_HEIGHT = 768; 

const Uint8* keyState;

SDL_Texture* backgroundTexture = NULL;
SDL_Texture* pipeTexture_down[4];
SDL_Texture* pipeTexture_up[4];
SDL_Texture* birdTexture = NULL;
SDL_Texture* birdtexture[3] = { NULL, NULL, NULL };
SDL_Texture* groundTexture = NULL;

SDL_Event event;
bool gameRunning = true;

const float timeStep = 0.01f;
float accumulator = 0.0f;
float currentTime = utils::HireTimeInSeconds();
float newTime = 0.0f;
float frameTime = 0.0f;
float alpha = 0.0f;
int startTicks;
int frameTicks;
const int PIPE_UP_MAX_Y = -10,
PIPE_UP_MIN_Y = -50,
PIPE_DOWN_MAX_Y = 180,
PIPE_DOWN_MIN_Y = 140;

float oneFlapTime = 0.3f;
float cTime = 0.0f;
int num = 0;
int num2 = 0;

bool Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has Failed. Error: " << SDL_GetError() << std::endl;

	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "SDL_image has Failed. Error: " << IMG_GetError() << std::endl;

	window.CreateWindow("Flappy Bird v1.0", SCREEN_WIDTH, SCREEN_HEIGHT);

	std::cout << "Refresh Rate: " << window.GetRefreshRate() << std::endl;

	//Loading Textures

	backgroundTexture = window.LoadTexture("res/gfx/Background.png");
	for (int i = 0; i < 4; i++)
	{
		pipeTexture_down[i] = window.LoadTexture("res/gfx/PipeDown.png");
		pipeTexture_up[i] = window.LoadTexture("res/gfx/PipeUp.png");
	}
	birdTexture = window.LoadTexture("res/gfx/Bird1.png");

	birdtexture[0] = window.LoadTexture("res/gfx/Bird1.png");
	birdtexture[1] = window.LoadTexture("res/gfx/Bird2.png");
	birdtexture[2] = window.LoadTexture("res/gfx/Bird3.png");


	groundTexture = window.LoadTexture("res/gfx/Ground1.png");


	return true;
}

bool load = Init();



Pipe pipe_down[4] = {
	Pipe(Vector(70, utils::RandomValues(PIPE_DOWN_MAX_Y, PIPE_DOWN_MIN_Y)), pipeTexture_down[0]), //down = 180 150
	Pipe(Vector(140, utils::RandomValues(PIPE_DOWN_MAX_Y, PIPE_DOWN_MIN_Y)), pipeTexture_down[0]),
	Pipe(Vector(210, utils::RandomValues(PIPE_DOWN_MAX_Y, PIPE_DOWN_MIN_Y)), pipeTexture_down[0]),
	Pipe(Vector(280, utils::RandomValues(PIPE_DOWN_MAX_Y, PIPE_DOWN_MIN_Y)), pipeTexture_down[0])
};

Pipe pipe_up[4] = {
	Pipe(Vector(70, utils::RandomValues(PIPE_UP_MAX_Y, PIPE_UP_MIN_Y)), pipeTexture_up[0]), //up = -50, -20
	Pipe(Vector(140, utils::RandomValues(PIPE_UP_MAX_Y, PIPE_UP_MIN_Y)), pipeTexture_up[1]),
	Pipe(Vector(210, utils::RandomValues(PIPE_UP_MAX_Y, PIPE_UP_MIN_Y)), pipeTexture_up[2]),
	Pipe(Vector(280, utils::RandomValues(PIPE_UP_MAX_Y, PIPE_UP_MIN_Y)), pipeTexture_up[3])
};

Bird bird(Vector(25, 96), birdTexture);

//Ground ground

void GameLoop()
{

	// pipe random generation
	srand(time(0));

	for (num = 0; num < 4; num++)
	{
		if (pipe_up[num].pipeCrossed)
		{
			pipe_up[num].SetPosition(Vector(pipe_up[num].GetPosition().GetX(), utils::RandomValues(PIPE_UP_MAX_Y, PIPE_UP_MIN_Y)));
			pipe_up[num].pipeCrossed = false;
		}

		if (pipe_down[num].pipeCrossed)
		{
			pipe_down[num].SetPosition(Vector(pipe_down[num].GetPosition().GetX(), utils::RandomValues(PIPE_DOWN_MAX_Y, PIPE_DOWN_MIN_Y)));
			pipe_down[num].pipeCrossed = false;
		}
	}

	//collision of bird and pipes


	for (num = 0; num < 4; num++)
	{
		if (utils::isCollide(bird, pipe_up[num]))
		{
			std::cout << " Bird colliding with Pipes" << std::endl;
		}
		else if (utils::isCollide(bird, pipe_down[num]))
		{
			std::cout << "Bird colliding with Pipes" << std::endl;
		}
	}


	utils::GetFramesRate();

	startTicks = SDL_GetTicks();

	newTime = utils::HireTimeInSeconds();
	frameTime = newTime - currentTime;
	currentTime = newTime;
	accumulator += frameTime;

	while (accumulator >= timeStep)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				{
					gameRunning = false;
					break;
				}

				case SDL_MOUSEBUTTONDOWN:
				{
					if (event.button.button == SDL_BUTTON_LEFT)
						bird.Fly();
					break;
				}
			}
			
		}
		accumulator -= timeStep;

	}

	alpha = accumulator / timeStep;

	for (int i = 0; i < 4; i++)
	{
		pipe_down[i].Update();
		pipe_up[i].Update();
	}

	bird.Update();
	window.Clear();

	window.Render(backgroundTexture, Vector(0, 0));

	for (int i = 0; i < 4; i++)
	{
		window.Render(pipe_down[i]);
		window.Render(pipe_up[i]);
	}
	//window.Render(bird);//54, 96

	window.Render(groundTexture, Vector(0, 200));

	if (cTime >= oneFlapTime)
	{
		cTime = 0.0f;
		num2 += 1;
		if (num2 > 2)
			num2 = 0;
	}
	cTime += 0.02f;
	window.Render(birdtexture[num2], bird.GetPosition());

	window.Display();

	frameTicks = SDL_GetTicks() - startTicks;
	if (frameTicks < 1000 / window.GetRefreshRate())
		SDL_Delay(1000 / window.GetRefreshRate() - frameTicks);
}

int main(int argc, char* args[])
{

	while (gameRunning)
	{
		GameLoop();
	}

	window.CleanUp();
	SDL_Quit();

	return 0;
}