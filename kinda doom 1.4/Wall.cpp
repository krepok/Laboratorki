#include "Wall.h"

Wall::Wall(SDL_FPoint _p1, SDL_FPoint _p2)
	: p1{ _p1 }, p2{ _p2 }, wallpaper{ nullptr }, isGIF{ false }, src{ {} }, fps{ 1 }, numOfFrames{ 1 }, counter{}
{
}

Wall::Wall(SDL_FPoint _p1, SDL_FPoint _p2, const char* picture, SDL_Renderer* renderer)
	: p1{ _p1 }, p2{ _p2 }, isGIF{ false }, src{ {} }, fps{ 1 }, numOfFrames{ 1 }, counter{}
{
	wallpaper = IMG_LoadTexture(renderer, picture);
}

Wall::Wall(SDL_FPoint _p1, SDL_FPoint _p2, const char* gif, SDL_FRect _src, int _fps, int _numOfFrames, SDL_Renderer* renderer)
	: p1{ _p1 }, p2{ _p2 }, src{ _src }, fps{ _fps }, isGIF{ true }, numOfFrames{ _numOfFrames }, counter{}
{
	wallpaper = IMG_LoadTexture(renderer, gif);
}

Walls::Walls(SDL_Renderer* _renderer, std::vector<Wall> _walls)
	: renderer{ _renderer }, walls{ _walls }
{
}

void Walls::render()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (const auto& wall : walls)
	{
		SDL_RenderLine(renderer, wall.p1.x, wall.p1.y, wall.p2.x, wall.p2.y);
	}
	increaseCounter();
}

void Walls::increaseCounter()
{
	for (auto& wall : this->walls)
	{
		static int counterForCounter{};
		counterForCounter = (counterForCounter + 1) % static_cast<int>((60 / wall.fps));

		if (counterForCounter == 0)
			wall.counter = (wall.counter + 1) % wall.numOfFrames;
	}
}
