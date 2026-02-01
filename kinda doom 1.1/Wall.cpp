#include "Wall.h"

Wall::Wall(SDL_FPoint _p1, SDL_FPoint _p2)
	: p1{ _p1 }, p2{ _p2 }, wallpaper{ nullptr }
{
}

Wall::Wall(SDL_FPoint _p1, SDL_FPoint _p2, const char* picture, SDL_Renderer* renderer)
	: p1{ _p1 }, p2{ _p2 }
{
	wallpaper = IMG_LoadTexture(renderer, picture);
}

Walls::Walls(SDL_Renderer* _renderer, std::vector<Wall> _walls)
	: renderer{ _renderer }, walls{ _walls }
{
}

void Walls::render() const
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (const auto& wall : walls)
	{
		SDL_RenderLine(renderer, wall.p1.x, wall.p1.y, wall.p2.x, wall.p2.y);
	}
}
