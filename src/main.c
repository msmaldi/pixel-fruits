#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "keyboard.h"

#include "game_core.h"
#include "game_state.h"

void
initialize()
{
    SDL_Init (SDL_INIT_EVERYTHING);
    IMG_Init (IMG_INIT_PNG);
	TTF_Init();
}

void
quit()
{
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void
game_update (void* data, Uint64 game_time)
{
    game_state_update ((GameState*)data, game_time);
}

void
game_draw (void* data, Uint64 game_time)
{
    game_state_draw ((GameState*)data, game_time);
}

int
main ()
{
    initialize();

    GameCore game = { 0 };
    GameState game_state;
	game_state_initialize (&game_state, &game);

	game_core_loop (&game_state, &game, game_update, game_draw);

    quit();

    return 0;
}
