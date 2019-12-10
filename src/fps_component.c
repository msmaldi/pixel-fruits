#include "fps_component.h"
#include "keyboard.h"

static bool current_is_pair = true;
static int seconds_pair = 0;
static int seconds_impair = 0;

static bool
is_pair (Uint64 n)
{
    return n % 2 == 0;
}

static void
count_frame ()
{
    Uint64 second = SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency();
    if (is_pair (second))
    {
        if (current_is_pair)
            seconds_pair++;
        else
        {
            seconds_pair = 0;
            seconds_impair++;
            current_is_pair = !current_is_pair;
        }
    }
    else
    {
        if (!current_is_pair)
            seconds_impair++;
        else
        {
            seconds_impair = 0;
            seconds_pair++;
            current_is_pair = !current_is_pair;
        }
    }
}

FpsComponent*
fps_component_new (int frames_per_sec, bool unlocked_frame, TTF_Font* font,
				   int x, int y, SDL_Color color)
{
    FpsComponent* fps_component = (FpsComponent*) calloc (1, sizeof (FpsComponent));

    fps_component->target_frame_time = SDL_GetPerformanceFrequency() / frames_per_sec;
    fps_component->unlocked_frame = unlocked_frame;

    fps_component->font = font;
    fps_component->x = x;
    fps_component->y = y;
	fps_component->color = color;

    return fps_component;
}

void
fps_component_update (FpsComponent* fps_component, Uint64 game_time)
{
	if (keyboard_is_key_released (SDL_SCANCODE_F1))
	{
		SDL_GL_SetSwapInterval (1);
		fps_component->unlocked_frame = true;
	}
	if (keyboard_is_key_released (SDL_SCANCODE_F2))
	{
		SDL_GL_SetSwapInterval (0);
		fps_component->unlocked_frame = false;
	}
	if (keyboard_is_key_released (SDL_SCANCODE_F3))
	{
		SDL_GL_SetSwapInterval (0);
		fps_component->unlocked_frame = true;
	}
}

void
fps_component_draw (FpsComponent* fps_component, SDL_Renderer* renderer, Uint64 game_time)
{
    count_frame();

    char text[20];
    snprintf (text, 20, "FPS: %u", current_is_pair ? seconds_impair : seconds_pair);

    SDL_Surface* text_surface = TTF_RenderText_Solid (fps_component->font, text, fps_component->color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface (renderer, text_surface);

    SDL_Rect rect = { fps_component->x, fps_component->y, text_surface->w, text_surface->h };
	SDL_RenderCopy (renderer, texture, NULL, &rect);

	SDL_FreeSurface (text_surface);
	SDL_DestroyTexture (texture);
}

void
fps_component_free (FpsComponent* fps_component)
{
    if (fps_component)
    {
        free (fps_component);
    }
}
