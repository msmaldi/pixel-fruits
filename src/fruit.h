#ifndef _FRUIT_H_
#define _FRUIT_H_

#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

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
} Fruit;

void    fruit_init     (Fruit* fruit, int32_t x, int32_t y);
void    fruit_draw     (Fruit* fruit, SDL_Renderer* renderer, Uint64 game_time);

#endif
