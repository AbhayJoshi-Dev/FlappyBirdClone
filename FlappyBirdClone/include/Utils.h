#pragma once

#include<SDL.h>

namespace utils
{
	int fps = 0;
	float startTime = 0.0f;
	float currentTime = 0.0f;
	
	inline float HireTimeInSeconds()
	{
		float t = SDL_GetTicks();
		t *= 0.001f;
		return t;
	}

	inline void GetFramesRate()
	{
		fps++;
		startTime = SDL_GetTicks();

		if ((startTime - currentTime) > 1000.0f)
		{
			currentTime = startTime;
			std::cout << fps << std::endl;
			fps = 0;
		}
	}

	inline int RandomValues(int p_max, int p_min)
	{

		return (rand() % (p_max - p_min + 1)) + p_min;
	}

	inline float Distance()
	{

	}
}