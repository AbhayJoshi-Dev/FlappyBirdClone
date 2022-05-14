#include<SDL.h>
#include<iostream>
#include<SDL_image.h>
#include<stdlib.h>
#include<time.h>
#include<SDL_ttf.h>

#include"RenderWindow.h"
#include"Entity.h"
#include"Pipe.h"
#include"Utils.h"
#include"Bird.h"
#include"Ground.h"
#include"Button.h"


bool Init();

bool load = Init();

RenderWindow window;

const int SCREEN_WIDTH = 432;
const int SCREEN_HEIGHT = 768; 

const Uint8* keyState;

SDL_Texture* backgroundTexture = NULL;
SDL_Texture* pipeTexture_down = NULL;
SDL_Texture* pipeTexture_up = NULL;
SDL_Texture* birdtexture[3] = { NULL, NULL, NULL };
SDL_Texture* groundTexture = NULL;
SDL_Texture* UI_GetReadyTexture = NULL;
SDL_Texture* UI_BirdTexture = NULL;
SDL_Texture* UI_HandTexture = NULL;
SDL_Texture* UI_TapTexture = NULL;
SDL_Texture* UI_OKButtonTexture = NULL;
SDL_Texture* UI_GameOverTexture = NULL;

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

float oneFlapTime = 0.2f;
float cTime = 0.0f;
int num = 0;
int num2 = 0;
bool start = false;
bool birdDead = false;
int mouseX, mouseY;
std::string scoreText;
float scoreTime = 0.f;
int currentScore = 0;
bool scoreOnce = false;

SDL_Color white = { 255, 255, 255 };

TTF_Font* font = TTF_OpenFont("res/font/font.ttf", 16);

bool Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has Failed. Error: " << SDL_GetError() << std::endl;

	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "SDL_image has Failed. Error: " << IMG_GetError() << std::endl;

	if (TTF_Init() == -1)
		std::cout << "SDL_ttf has Failed. Error: " << TTF_GetError() << std::endl;

	window.CreateWindow("Flappy Bird", SCREEN_WIDTH, SCREEN_HEIGHT);

	std::cout << "Refresh Rate: " << window.GetRefreshRate() << std::endl;

	//Loading Textures

	backgroundTexture = window.LoadTexture("res/gfx/Background.png");

	pipeTexture_down = window.LoadTexture("res/gfx/PipeDown.png");
	pipeTexture_up = window.LoadTexture("res/gfx/PipeUp.png");

	birdtexture[0] = window.LoadTexture("res/gfx/Bird1.png");
	birdtexture[1] = window.LoadTexture("res/gfx/Bird2.png");
	birdtexture[2] = window.LoadTexture("res/gfx/Bird3.png");

	groundTexture = window.LoadTexture("res/gfx/Ground1.png");

	UI_GetReadyTexture = window.LoadTexture("res/gfx/GetReadyText.png");
	UI_BirdTexture = window.LoadTexture("res/gfx/Bird4.png");
	UI_HandTexture = window.LoadTexture("res/gfx/TutorialHand.png");
	UI_TapTexture = window.LoadTexture("res/gfx/Tap.png");
	UI_OKButtonTexture = window.LoadTexture("res/gfx/OkButton.png");
	UI_GameOverTexture = window.LoadTexture("res/gfx/GameOverText.png");


	return true;
}

float pipe_X_pos[4] = { 280.f, 350.f, 420.f, 490.f };

Pipe pipe_down[4] = {
	Pipe(Vector(pipe_X_pos[0], (float)utils::RandomValues(PIPE_DOWN_MAX_Y, PIPE_DOWN_MIN_Y)), pipeTexture_down),
	Pipe(Vector(pipe_X_pos[1], (float)utils::RandomValues(PIPE_DOWN_MAX_Y, PIPE_DOWN_MIN_Y)), pipeTexture_down),
	Pipe(Vector(pipe_X_pos[2], (float)utils::RandomValues(PIPE_DOWN_MAX_Y, PIPE_DOWN_MIN_Y)), pipeTexture_down),
	Pipe(Vector(pipe_X_pos[3], (float)utils::RandomValues(PIPE_DOWN_MAX_Y, PIPE_DOWN_MIN_Y)), pipeTexture_down)
};

Pipe pipe_up[4] = {
	Pipe(Vector(pipe_X_pos[0], (float)utils::RandomValues(PIPE_UP_MAX_Y, PIPE_UP_MIN_Y)), pipeTexture_up),
	Pipe(Vector(pipe_X_pos[1], (float)utils::RandomValues(PIPE_UP_MAX_Y, PIPE_UP_MIN_Y)), pipeTexture_up),
	Pipe(Vector(pipe_X_pos[2], (float)utils::RandomValues(PIPE_UP_MAX_Y, PIPE_UP_MIN_Y)), pipeTexture_up),
	Pipe(Vector(pipe_X_pos[3], (float)utils::RandomValues(PIPE_UP_MAX_Y, PIPE_UP_MIN_Y)), pipeTexture_up)
};

Ground ground[2] = {
	Ground(Vector(0.f, 200.f), groundTexture),
	Ground(Vector(154.f, 200.f), groundTexture)
};

Bird bird(Vector(25, 96), birdtexture[0]);

Button OkButton(Vector(50.f, 150.f), UI_OKButtonTexture);

void MenuReset();

void GameLoop()
{

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
					{
						bird.Fly();
						if (!start)
						{
							start = true;
						}
						if (utils::IsCollide((float)mouseX / 3, (float)mouseY / 3, OkButton) && birdDead)
						{
							MenuReset();
						}
					}
					break;
				}
			}
			
		}
		accumulator -= timeStep;

	}

	alpha = accumulator / timeStep;

	window.Clear();

	window.Render(backgroundTexture, Vector(0, 0));


	// pipe random generation
	srand((unsigned int)time(0));

	for (num = 0; num < 4; num++)
	{
		if (pipe_up[num].pipeCrossed)
		{
			pipe_up[num].SetPosition(Vector(pipe_up[num].GetPosition().GetX(), (float)utils::RandomValues(PIPE_UP_MAX_Y, PIPE_UP_MIN_Y)));
			pipe_up[num].pipeCrossed = false;
		}

		if (pipe_down[num].pipeCrossed)
		{
			pipe_down[num].SetPosition(Vector(pipe_down[num].GetPosition().GetX(), (float)utils::RandomValues(PIPE_DOWN_MAX_Y, PIPE_DOWN_MIN_Y)));
			pipe_down[num].pipeCrossed = false;
		}
	}

	if (scoreOnce)
	{
		scoreTime += 0.007f;
		if (scoreTime >= 1.f)
		{
			scoreTime = 0.f;
			scoreOnce = false;
		}
	}

	//collision of bird and pipes
	if (!birdDead)
	{
		for (num = 0; num < 4; num++)
		{
			if (utils::IsCollide(bird, pipe_up[num]))
			{
				birdDead = true;
			}
			else if (utils::IsCollide(bird, pipe_down[num]))
			{
				birdDead = true;
			}
			else if (utils::IsTrigger(bird, pipe_down[num].GetPosition().GetX() + (pipe_down[num].GetCurrentFrame().w / 2.f), pipe_down[num].GetPosition().GetY(), 100.f) && !scoreOnce)
			{
				scoreOnce = true;
				currentScore += 1;
			}

			if (num < 2)
				if (utils::IsCollide(bird, ground[num]))
				{
					birdDead = true;
				}
		}
	}


	//render pipes
	if (start)
	{
		for (int i = 0; i < 4; i++)
		{
			if (!birdDead)
			{
				pipe_down[i].Update();
				pipe_up[i].Update();
			}
			window.Render(pipe_down[i]);
			window.Render(pipe_up[i]);
		}
	}

	//UI main menu
	if (!start)
	{
		window.Render(UI_GetReadyTexture, Vector(25.f, 50.f));
		window.Render(UI_BirdTexture, Vector(55.f, 100.f));
		window.Render(UI_HandTexture, Vector(60.f, 120.f));
		window.Render(UI_TapTexture, Vector(73.f, 130.f));


		bird.SetGravity(0.f, 0.f);
		bird.Wave();
	}
	else
	{
		if (!birdDead)
		{
			bird.SetGravity(0.f, 0.04f);
			bird.Update();
		}
	}

	//ground render
	for (num = 0; num < 2; num++)
	{
		if (!birdDead)
		{
			ground[num].Update();
		}
		window.Render(ground[num]);
	}

	//bird render
	if (!birdDead)
	{
		if (cTime >= oneFlapTime)
		{
			cTime = 0.0f;
			num2 += 1;
			if (num2 > 2)
				num2 = 0;
		}
		cTime += 0.02f;
		window.RenderRotate(birdtexture[num2], bird.GetPosition(), bird.GetAngle());
	}
	else
	{
		window.RenderRotate(birdtexture[0], bird.GetPosition(), bird.GetAngle());
	}

	//game over ui
	if (birdDead)
	{
		window.Render(OkButton);
		window.Render(UI_GameOverTexture, Vector(25.f, 50.f));
		SDL_GetMouseState(&mouseX, &mouseY);
	}

	if (start)
	{
		window.RenderText(200.f, 10.f, currentScore, font, white);
	}

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
	TTF_Quit();
	SDL_Quit();

	return 0;
}

void MenuReset()
{

	bird.SetPosition(Vector(25.f, 110.f));
	bird.SetAngle(0.f);

	for (int i = 0; i < 4; i++)
	{
		pipe_down[i].SetPosition(Vector(pipe_X_pos[i], (float)utils::RandomValues(PIPE_DOWN_MAX_Y, PIPE_DOWN_MIN_Y)));
		pipe_up[i].SetPosition(Vector(pipe_X_pos[i], (float)utils::RandomValues(PIPE_UP_MAX_Y, PIPE_UP_MIN_Y)));
	}

	currentScore = 0;
	start = false;
	birdDead = false;
}