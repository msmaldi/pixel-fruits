#include "game_state.h"
#include "keyboard.h"
#include "math.h"
#include "logf.h"

typedef struct
{
    SDL_Scancode scan_code;
    Player* player;
} Command;

static void
handle_key_release (GameState* game, SDL_Scancode scan_code)
{
    Command c = { scan_code, game->current_player };

    observer_notify_all (&game->observers, &c);
}

static void
keyboard_listener_update (GameState* game)
{
    for (SDL_Scancode scan_code = SDL_SCANCODE_UNKNOWN; scan_code < SDL_NUM_SCANCODES; scan_code++)
        if (keyboard_is_key_released (scan_code))
            handle_key_release (game, scan_code);
}

static void
arrow_up (Player* player)
{
    game_logf ("Moving Player Up\n");
    if (player->y > 0)
        player->y -= 1;
}

static void
arrow_down (Player* player)
{
    game_logf ("Moving Player Down\n");
    if (player->y < GRID_SIZE - 1)
        player->y += 1;
}

static void
arrow_right (Player* player)
{
    game_logf ("Moving Player Right\n");
    if (player->x < GRID_SIZE - 1)
        player->x += 1;
}

static void
arrow_left (Player* player)
{
    game_logf ("Moving Player Left\n");
    if (player->x > 0)
        player->x -= 1;
}

const void (*accepted_moves[SDL_NUM_SCANCODES])(Player* player) = { 0 };

static void
move_player (void* data)
{
    Command* c = data;

    if (accepted_moves[c->scan_code])
        accepted_moves[c->scan_code](c->player);
}

void
game_state_initialize (GameState* game_state, GameCore* game_core)
{
    game_core_initialize (game_core, "Pixel Fruits");
    game_state->game_core = game_core;

    keyboard_initialize ();

    game_state->current_player = &game_state->players[0];
    player_init (game_state->current_player, 0, 0, "Player 1");

    Fruit* fruit = &game_state->fruits[0];
    fruit->is_active = true;
    fruit->x = 3;
    fruit->y = 3;

    accepted_moves[SDL_SCANCODE_UP] = accepted_moves[SDL_SCANCODE_W] = arrow_up;
    accepted_moves[SDL_SCANCODE_DOWN] = accepted_moves[SDL_SCANCODE_S] = arrow_down;
    accepted_moves[SDL_SCANCODE_RIGHT] = accepted_moves[SDL_SCANCODE_D] = arrow_right;
    accepted_moves[SDL_SCANCODE_LEFT] = accepted_moves[SDL_SCANCODE_A] = arrow_left;

    observer_subscribe (&game_state->observers, move_player);
}

void
check_collision (GameState* game_state)
{
    for (int p = 0; p < MAX_PLAYERS; p++)
    {
        Player* player = &game_state->players[p];
        if (!player->is_active)
            continue;
        for (int f = 0; f < MAX_FRUITS; f++)
        {
            Fruit* fruit = &game_state->fruits[f];
            if (fruit->is_active && player->position == fruit->position)
            {
                game_logf ("Player %s get a Fruit\n", player->player_id);
                fruit->is_active = false;
            }
        }
    }
}

void
game_state_update (GameState* game_state, Uint64 game_time)
{
    keyboard_listener_update (game_state);

    check_collision (game_state);

    game_core_update (game_state->game_core, game_time);
}

void
grid_draw (SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor (renderer, 225, 225, 225, 255);
    SDL_Rect grid = { BORDER_SIZE, BORDER_SIZE, MAP_SIZE, MAP_SIZE };
    SDL_RenderFillRect (renderer, &grid);
}

void
game_state_draw (GameState* game_state, Uint64 game_time)
{
    SDL_Renderer* renderer = game_state->game_core->renderer;

    grid_draw (renderer);

    for (int i = 0; i < MAX_FRUITS; i++)
    {
        Fruit* fruit = &game_state->fruits[i];
        if (fruit->is_active)
            fruit_draw (fruit, renderer, game_time);
    }

    const SDL_Color blue = { 0, 0, 255, 255 };
    player_draw (game_state->current_player, renderer, &blue);

    game_core_draw (game_state->game_core, game_time);
}
