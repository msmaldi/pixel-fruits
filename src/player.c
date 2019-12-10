#include "player.h"
#include "config.h"

void
player_init (Player* player, int32_t x, int32_t y, const char* player_id)
{
    player->is_active = true;
    player->x = x;
    player->y = y;
    strncat (player->player_id, player_id, 256);
}

void
player_draw (Player* player, SDL_Renderer* renderer, const SDL_Color* color)
{
    int x = player->x * OBJECTS_SIZE + BORDER_SIZE;
    int y = player->y * OBJECTS_SIZE + BORDER_SIZE;
    SDL_Rect rect = { x, y, OBJECTS_SIZE, OBJECTS_SIZE };

    SDL_SetRenderDrawColor (renderer, color->r, color->g, color->b, color->a);
    SDL_RenderFillRect (renderer, &rect);
}
