#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <stdbool.h>
#include "config.h"

typedef struct Player {
    SDL_Rect rect;
    SDL_Color color;

    SDL_Scancode leftKey;
    SDL_Scancode rightKey;
    SDL_Scancode upKey;
    SDL_Scancode downKey;

    int speed;
    int jumpStrength;
    bool jumping;

} Player;

void drawPlayer(Player *player, SDL_Renderer *renderer);
void movePlayer(Player *player, const Uint8 *state);
void jumpPlayer(Player *player, const Uint8 *state);

#endif