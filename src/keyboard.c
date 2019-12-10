#include "keyboard.h"

static Uint8 current_keyboard_state[SDL_NUM_SCANCODES];
static Uint8 previous_keyboard_state[SDL_NUM_SCANCODES];

void
keyboard_initialize()
{
    memset (previous_keyboard_state, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
    memcpy (current_keyboard_state, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);
}

void
keyboard_update()
{
    memcpy (previous_keyboard_state, current_keyboard_state, sizeof(Uint8) * SDL_NUM_SCANCODES);
    memcpy (current_keyboard_state, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);
}

bool
keyboard_is_key_triggered (const SDL_Scancode key_code)
{
    return current_keyboard_state[key_code] && !previous_keyboard_state[key_code];
}

bool
keyboard_is_key_pressed (const SDL_Scancode key_code)
{
    return current_keyboard_state[key_code];
}

bool
keyboard_is_key_released (const SDL_Scancode key_code)
{
    return !current_keyboard_state[key_code] && previous_keyboard_state[key_code];
}
