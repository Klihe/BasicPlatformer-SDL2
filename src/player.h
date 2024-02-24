#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <stdbool.h>

#include "map.h"
#include "config.h"

typedef struct Player {
    SDL_Rect rect;
    SDL_Color color;

    int speed;
    int prevX;
    int prevY;

    SDL_Scancode leftKey;
    SDL_Scancode rightKey;
    SDL_Scancode upKey;
    SDL_Scancode downKey;

    // bool fall;
    bool ladder;
    bool ladderDown;

} Player;

void drawPlayer(Player *player, SDL_Renderer *renderer);
void movePlayer(Player *player, const Uint8 *state);
void handlePlayerCollision(Player *player, Map *map);

#endif