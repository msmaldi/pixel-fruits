#ifndef _GAME_CORE_H_
#define _GAME_CORE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "keyboard.h"
#include "fps_component.h"

typedef struct
{
    bool running;
	SDL_Window* window;
	SDL_Renderer* renderer;

	TTF_Font* font;
	FpsComponent* fps_component;
} GameCore;

void    game_core_initialize  (GameCore* game, const char* window_title);
void    game_core_loop        (void* game_state, GameCore* game, void (*game_update)(void*, Uint64), void (*game_draw)(void*, Uint64));
void    game_core_update      (GameCore* game, Uint64 game_time);
void    game_core_draw        (GameCore* game, Uint64 game_time);

#endif
