#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "Player.h"
#include "Wall.h"

static SDL_Window* window;
static SDL_Renderer* renderer;
Player* player{ nullptr };
Walls* walls{ nullptr };

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("kinda_doom", 2560, 1080, 0, &window, &renderer);

	player = new Player{ renderer };

	Wall separator{ { 1280, 0 }, {1280, 1080} };
	Wall wall1{ {100, 100}, {100, 1000} };
	Wall wall2{ {1000, 100}, {1200, 1000} };
	Wall wall3{ { 100,100 }, {1000, 100} };
	Wall wall4{ {100, 1000}, {1200, 1000} };

	walls = new Walls{ renderer, {separator, wall1, wall2, wall3, wall4} };

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	player->render();
	walls->render();

	const bool* keys{ SDL_GetKeyboardState(NULL) };
	if (keys[SDL_SCANCODE_W])
	{
		player->walkWnew(*walls);
	}
	if (keys[SDL_SCANCODE_S])
	{
		player->walkSnew(*walls);
	}
	if (keys[SDL_SCANCODE_A])
	{
		player->walkAnew(*walls);
	}
	if (keys[SDL_SCANCODE_D])
	{
		player->walkDnew(*walls);
	}
	if (keys[SDL_SCANCODE_LEFT])
	{
		player->turnLeft(*walls);
	}
	if (keys[SDL_SCANCODE_RIGHT])
	{
		player->turnRight(*walls);
	}

	SDL_FRect screen{ 1281, 0, 1280, 1080 };

	player->to3D(screen);

	SDL_RenderPresent(renderer);
	SDL_Delay(16);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_EVENT_QUIT:
		return SDL_APP_SUCCESS;

	default:
		break;
	}

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{ }