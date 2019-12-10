#include "fruit.h"
#include "config.h"

void
fruit_init (Fruit* fruit, int32_t x, int32_t y)
{
    fruit->is_active = true;
    fruit->x = x;
    fruit->y = y;
}

void
fruit_draw (Fruit* fruit, SDL_Renderer* renderer, Uint64 game_time)
{
    int x = fruit->x * OBJECTS_SIZE + BORDER_SIZE;
    int y = fruit->y * OBJECTS_SIZE + BORDER_SIZE;
    SDL_Rect rect = { x, y, OBJECTS_SIZE, OBJECTS_SIZE };

    SDL_SetRenderDrawColor (renderer, 0, 255, 0, 255);
    SDL_RenderFillRect (renderer, &rect);
}
