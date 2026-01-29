#pragma once
#include <SDL3/SDL.h>
#include <vector>

struct Wall
{
	SDL_FPoint p1;
	SDL_FPoint p2;

	Wall(SDL_FPoint _p1, SDL_FPoint _p2);
};

struct Walls
{
	SDL_Renderer* renderer;
	std::vector<Wall> walls;

	Walls(SDL_Renderer*, std::vector<Wall>);
	void render() const;
};
