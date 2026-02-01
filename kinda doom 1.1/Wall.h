#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>

struct Wall
{
	SDL_FPoint p1;
	SDL_FPoint p2;

	SDL_Texture* wallpaper;

	Wall(SDL_FPoint, SDL_FPoint);
	Wall(SDL_FPoint, SDL_FPoint, const char*, SDL_Renderer*);
};

struct Walls
{
	SDL_Renderer* renderer;
	std::vector<Wall> walls;

	Walls(SDL_Renderer*, std::vector<Wall>);
	void render() const;
};
