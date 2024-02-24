#ifndef PLAYER_H
#define PLAYER_H

// include libraries
#include <SDL.h>
#include <stdbool.h>

// include files
#include "map.h"
#include "config.h"

// define player struct
typedef struct Player {
    // visual representation
    SDL_Rect rect;
    SDL_Color color;

    // movement
    int speed;
    int prevX;
    int prevY;

    // input
    SDL_Scancode leftKey;
    SDL_Scancode rightKey;
    SDL_Scancode upKey;
    SDL_Scancode downKey;

    // state
        // bool fall;
    bool ladder;
    bool ladderDown;

} Player;

// player's functions
void drawPlayer(Player *player, SDL_Renderer *renderer);
void movePlayer(Player *player, const Uint8 *state);
void handlePlayerCollision(Player *player, Map *map);

#endif