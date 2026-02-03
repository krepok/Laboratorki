#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "Player.h"
#include "Wall.h"
#include "Projectile.h"
#include <chrono>

static SDL_Window* window;
static SDL_Renderer* renderer;
Player* player{ nullptr };
Walls* wallsTexture{ nullptr };
Walls* wallsCollision{ nullptr };
Projectiles* projectiles{ nullptr };

int counter{};
auto start = std::chrono::steady_clock::now();

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
	Wall wall5{ {100, 500}, {1000, 500}, "assets/masha.png", renderer};

	Wall pasha{ {100, 100}, {200, 100}, "assets/pasha ne nogi.jpg", renderer };
	Wall kirill{ {200, 100}, {300, 100}, "assets/kirill nogi.jpg", renderer };
	Wall ildar{ {300, 100}, {400, 100}, "assets/ildar.jpg", renderer };
	Wall ilya{ {400, 100}, {500, 100}, "assets/ilya.jpg", renderer };
	Wall pashaNogi{ {500, 100}, {600, 100}, "assets/pasha.jpg", renderer };
	Wall maksim{ {600, 100}, {700, 100}, "assets/maksim.jpg", renderer };
	Wall mustard{ {100, 200}, {200, 200}, "assets/mustard.png", renderer };
	Wall komrak{ {100, 500}, {500, 500}, "assets/komrak.png", {0, 0, 800, 800}, 20, 290, renderer };

	Wall explosionTest1{ {100, 100}, {200, 100}, "assets/explosion (1).png", {0, 0, 32, 32}, 24, 16, renderer };
	Wall explosionTest2{ {200, 100}, {300, 100}, "assets/explosion (2).png", {0, 0, 32, 32}, 24, 16, renderer };
	Wall explosionTest3{ {300, 100}, {400, 100}, "assets/explosion (3).png", {0, 0, 32, 32}, 24, 16, renderer };
	Wall explosionTest4{ {400, 100}, {500, 100}, "assets/explosion (4).png", {0, 0, 32, 32}, 24, 16, renderer };
	Wall explosionTest5{ {500, 100}, {600, 100}, "assets/explosion (5).png", {0, 0, 32, 32}, 24, 16, renderer };
	Wall explosionTest6{ {600, 100}, {700, 100}, "assets/explosion (6).png", {0, 0, 32, 32}, 24, 16, renderer };
	Wall explosionTest7{ {700, 100}, {800, 100}, "assets/explosion (7).png", {0, 0, 64, 64}, 24, 16, renderer };
	Wall explosionTest8{ {800, 100}, {900, 100}, "assets/explosion (8).png", {0, 0, 32, 32}, 24, 16, renderer };
	Wall explosionTest9{ {900, 100}, {1000, 100}, "assets/explosion (9).png", {0, 0, 32, 32}, 24, 16, renderer };
	Wall explosionTest10{ {1000, 100}, {1100, 100}, "assets/explosion (10).png", {0, 0, 64, 64}, 24, 16, renderer };


	//kirill ,ildar, ilya, pashaNogi, maksim, wall1, wall2, wall3, wall4, pasha, mustard

	//explosionTest1, explosionTest2, explosionTest3, explosionTest4, explosionTest5, explosionTest6, explosionTest7, explosionTest8, explosionTest9, explosionTest10

	wallsTexture = new Walls{ renderer, {separator, pasha, mustard, kirill ,ildar, ilya, pashaNogi, maksim, komrak} };

	wallsCollision = new Walls{ renderer, {separator, kirill ,ildar, ilya, pashaNogi, maksim, pasha, mustard, komrak} };

	projectiles = new Projectiles{ {} };

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
	auto start2 = std::chrono::steady_clock::now();
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	player->render();

	projectiles->move(*wallsTexture, *player, *wallsCollision);
	wallsTexture->render();

	const bool* keys{ SDL_GetKeyboardState(NULL) };
	if (keys[SDL_SCANCODE_W])
	{
		player->walkWnew(*wallsTexture, *wallsCollision);
	}
	if (keys[SDL_SCANCODE_S])
	{
		player->walkSnew(*wallsTexture, *wallsCollision);
	}
	if (keys[SDL_SCANCODE_A])
	{
		player->walkAnew(*wallsTexture, *wallsCollision);
	}
	if (keys[SDL_SCANCODE_D])
	{
		player->walkDnew(*wallsTexture, *wallsCollision);
	}
	if (keys[SDL_SCANCODE_LEFT])
	{
		player->turnLeft(*wallsTexture);
	}
	if (keys[SDL_SCANCODE_RIGHT])
	{
		player->turnRight(*wallsTexture);
	}

	SDL_FRect screen{ 1281, 0, 1280, 1080 };

	player->to3D(screen);

	SDL_RenderPresent(renderer);

	auto end = std::chrono::steady_clock::now();;
	auto elapsed2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start2);

	if (elapsed2.count() < 1000 / worldFps)
		SDL_Delay(1000 / worldFps - elapsed2.count());

	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	if (elapsed.count() >= 1000)
	{
		std::cout << counter << '\n';
		counter = 0;
		start = end;
	}
	else
	{
		counter++;
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_EVENT_QUIT:
		return SDL_APP_SUCCESS;

	case SDL_EVENT_KEY_UP:
		if (event->key.scancode == SDL_SCANCODE_F)
		{
			Projectile pr{*player, *wallsTexture};
			projectiles->projectiles.push_back(pr);
			player->getPoints(*wallsTexture);
		}
		break;

	default:
		break;
	}

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{ }