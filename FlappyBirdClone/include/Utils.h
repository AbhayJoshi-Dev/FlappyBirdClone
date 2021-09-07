#pragma once

#include<SDL.h>

namespace utils
{
	int fps = 0;
	float startTime = 0.0f;
	float currentTime = 0.0f;
	
	inline float HireTimeInSeconds()
	{
		float t = (float)SDL_GetTicks();
		t *= 0.001f;
		return t;
	}

	inline void GetFramesRate()
	{
		fps++;
		startTime = (float)SDL_GetTicks();

		if ((startTime - currentTime) > 1000.0f)
		{
			currentTime = startTime;
			std::cout << "Frames per second (fps):" << fps << std::endl;
			fps = 0;
		}
	}

	inline int RandomValues(int p_max, int p_min)
	{

		return (rand() % (p_max - p_min + 1)) + p_min;
	}

	inline float Distance(Vector p1, Vector p2)
	{
		float dx = p1.GetX() - p2.GetX();
		float dy = p1.GetY() - p2.GetY();

		return sqrt(dx * dx + dy * dy);
	}

	inline float DistanceXY(float x1, float x2, float y1, float y2)
	{
		float dx = x1 - x2;
		float dy = y1 - y2;

		return sqrt(dx * dx + dy * dy);
	}

	inline bool RangeIntersect(float min0, float max0, float min1, float max1)
	{
		return  std::max(min0, max0) >= std::min(min1, max1) && 
			std::min(min0, max0) <= std::max(min1, max1);
	}

	inline bool IsCollide(Entity r1, Entity r2)
	{
		return RangeIntersect(r1.GetPosition().GetX(), r1.GetPosition().GetX() + (float)r1.GetCurrentFrame().w, r2.GetPosition().GetX(), r2.GetPosition().GetX() + (float)r2.GetCurrentFrame().w) &&
			RangeIntersect(r1.GetPosition().GetY(), r1.GetPosition().GetY() + (float)r1.GetCurrentFrame().h, r2.GetPosition().GetY(), r2.GetPosition().GetY() + (float)r2.GetCurrentFrame().h);
	};

	inline bool InRange(float min, float max, float value)
	{
		return value >= std::min(min, max) && value <= std::max(min, max);
	}

	inline bool IsCollide(float x, float y, Entity entity)
	{
		return InRange(entity.GetPosition().GetX(), entity.GetPosition().GetX() + entity.GetCurrentFrame().w, x) &&
			InRange(entity.GetPosition().GetY(), entity.GetPosition().GetY() + entity.GetCurrentFrame().h, y);
	}
}