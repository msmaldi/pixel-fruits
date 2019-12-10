#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct
{
    bool is_active;
    union
    {
        int64_t position;
        struct
        {
            int32_t x;
            int32_t y;
        };
    };
    char player_id[256];
} Player;

void    player_init     (Player* player, int32_t x, int32_t y, const char* player_id);
void    player_draw     (Player* player, SDL_Renderer* renderer, const SDL_Color* color);

#endif
