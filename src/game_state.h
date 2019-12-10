#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "config.h"

#include "player.h"
#include "fruit.h"
#include "observer.h"

#include "game_core.h"

typedef struct
{
    GameCore* game_core;

    Player* current_player;
    Player players[MAX_PLAYERS];
    Fruit fruits[MAX_FRUITS];

    Observer observers;
} GameState;

extern GameState game_state;

void    game_state_initialize  (GameState* game, GameCore* game_core);
void    game_state_update      (GameState* game, Uint64 game_time);
void    game_state_draw        (GameState* game, Uint64 game_time);

#endif
