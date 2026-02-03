#include "Wall.h"

Wall::Wall()
	: p1{ 0, 0 }, p2{ 0, 0 }, wallpaper{ nullptr }, isGIF{ false }, src{ {} }, fps{ 1 }, numOfFrames{ 1 }, counter{}, counterForFps{}
{
}

Wall::Wall(SDL_FPoint _p1, SDL_FPoint _p2)
	: p1{ _p1 }, p2{ _p2 }, wallpaper{ nullptr }, isGIF{ false }, src{ {} }, fps{ 1 }, numOfFrames{ 1 }, counter{}, counterForFps{}
{
}

Wall::Wall(SDL_FPoint _p1, SDL_FPoint _p2, const char* picture, SDL_Renderer* renderer)
	: p1{ _p1 }, p2{ _p2 }, isGIF{ false }, src{ {} }, fps{ 1 }, numOfFrames{ 1 }, counter{}, counterForFps{}
{
	wallpaper = IMG_LoadTexture(renderer, picture);
}

Wall::Wall(SDL_FPoint _p1, SDL_FPoint _p2, const char* gif, SDL_FRect _src, int _fps, int _numOfFrames, SDL_Renderer* renderer)
	: p1{ _p1 }, p2{ _p2 }, src{ _src }, fps{ _fps }, isGIF{ true }, numOfFrames{ _numOfFrames }, counter{}, counterForFps{}
{
	wallpaper = IMG_LoadTexture(renderer, gif);
}

Wall::Wall(const Wall& wall)
	: p1{ wall.p1 }, p2{ wall.p2 }, wallpaper{ wall.wallpaper }, isGIF{ wall.isGIF }, src{ wall.src }, fps{ wall.fps }, numOfFrames{ wall.numOfFrames }, counter{wall.counter}, counterForFps{}
{
}

Wall::Wall(Wall&& wall)
	: p1{ wall.p1 }, p2{ wall.p2 }, wallpaper{ wall.wallpaper }, isGIF{ wall.isGIF }, src{ wall.src }, fps{ wall.fps }, numOfFrames{ wall.numOfFrames }, counter{ wall.counter }, counterForFps{}
{
	wall.wallpaper = nullptr;
}

Wall& Wall::operator=(const Wall& wall)
{
	this->p1 = wall.p1;
	this->p2 = wall.p2;
	this->wallpaper = wall.wallpaper;
	this->isGIF = wall.isGIF;
	this->src = wall.src;
	this->fps = wall.fps;
	this->numOfFrames = wall.numOfFrames;
	this->counter = wall.counter;
	this->counterForFps = wall.counterForFps;
	return *this;
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
		if (wall.fps > 60)
		{
			wall.fps = 60;
		}
		wall.counterForFps = (wall.counterForFps + 1) % static_cast<int>((60 / wall.fps));

		if (wall.counterForFps == 0)
			wall.counter = (wall.counter + 1) % wall.numOfFrames;
	}
}
