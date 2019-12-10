#ifndef _FPS_COMPONENT_H_
#define _FPS_COMPONENT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef struct
{
	bool unlocked_frame;
	Uint64 target_frame_time;
    TTF_Font* font;
    int x;
    int y;
    SDL_Color color;
} FpsComponent;

FpsComponent* fps_component_new     (int target_frame_time, bool unlocked_frame, TTF_Font* font,
                                     int x, int y, SDL_Color color);
void          fps_component_update  (FpsComponent* fps_component, Uint64 game_time);
void          fps_component_draw    (FpsComponent* fps_component, SDL_Renderer* renderer, Uint64 game_time);
void          fps_component_free    (FpsComponent* fps_component);

#endif
