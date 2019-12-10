#include "game_core.h"

#include "config.h"

void
game_core_loop (void* game_state, GameCore *game_core, void (*game_update)(void*, Uint64), void (*game_draw)(void*, Uint64))
{
	SDL_Event event;
	Uint64 drawFrameTime = SDL_GetPerformanceCounter();
	Uint64 lpcDraw = SDL_GetPerformanceCounter();
	Uint64 lpcUpdate = SDL_GetPerformanceCounter();
	Uint64 deltaGameTime = 0;
	while (game_core->running)
	{
 		while (SDL_PollEvent (&event) != 0)
 			if (event.type == SDL_QUIT)
 				game_core->running = false;

		Uint64 currentPerformanceCounter = SDL_GetPerformanceCounter();
		game_update (game_state, currentPerformanceCounter - lpcUpdate);
		lpcUpdate = currentPerformanceCounter;

		if (game_core->fps_component->unlocked_frame)
		{
			game_draw (game_state, currentPerformanceCounter - lpcDraw);
			lpcDraw = currentPerformanceCounter;
		}
		else if (drawFrameTime < currentPerformanceCounter)
		{
			game_draw (game_state, currentPerformanceCounter - lpcDraw);
			lpcDraw = currentPerformanceCounter;
			drawFrameTime += game_core->fps_component->target_frame_time;
		}
	}
}

void
game_core_initialize (GameCore *game, const char* window_title)
{
	game->running = true;
	game->window = SDL_CreateWindow (window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	game->renderer = SDL_CreateRenderer (game->window, -1, SDL_RENDERER_ACCELERATED);

	game->font = TTF_OpenFont ("content/Anonymous_Pro.ttf", 32);
    const SDL_Color WHITE = { 255, 255, 255 };
	game->fps_component = fps_component_new (240, true, game->font, SCREEN_WIDTH - 200, 10, WHITE);
}

void
game_core_update (GameCore* game, Uint64 game_time)
{
	fps_component_update (game->fps_component, game_time);
	keyboard_update();
}

void
game_core_draw (GameCore* game, Uint64 game_time)
{
	fps_component_draw (game->fps_component, game->renderer, game_time);
	SDL_RenderPresent (game->renderer);

    SDL_SetRenderDrawColor (game->renderer, 204, 204, 204, 255);
	SDL_RenderClear (game->renderer);
}
