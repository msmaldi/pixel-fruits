#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <SDL2/SDL.h>
#include <stdbool.h>

void    keyboard_initialize         ();
void    keyboard_update             ();
bool    keyboard_is_key_triggered   (const SDL_Scancode key_code);
bool    keyboard_is_key_pressed     (const SDL_Scancode key_code);
bool    keyboard_is_key_released    (const SDL_Scancode key_code);

#endif
