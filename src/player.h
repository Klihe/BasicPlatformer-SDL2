#ifndef PLAYER_H
#define PLAYER_H

// include libraries
#include <SDL.h>
#include <stdbool.h>

// include files
#include "map.h"
#include "config.h"

enum FaceDirection {
    FACE_LEFT,
    FACE_RIGHT
};

enum MapType {
    MAP1,
    MAP2
};

// define player struct
typedef struct Player {
    // visual representation
    SDL_Rect rect;
    SDL_Color color;
    enum MapType mapType;

    // movement
    int speed;
    float speedMultiplier;
    int prevX;
    int prevY;

    // input
    SDL_Scancode leftKey;
    SDL_Scancode rightKey;
    SDL_Scancode upKey;
    SDL_Scancode downKey;
    SDL_Scancode sprintKey;
    SDL_Scancode meleeAttackKey;
    SDL_Scancode rangedAttackKey;
    SDL_Scancode openTreasureKey;

    // state
        // bool fall;
    enum FaceDirection faceDirection;
    bool ladder;
    bool ladderDown;
    bool meleeAttackActive;
    int meleeAttackTime;
    bool rangedAttackActive;
    int rangedAttackTime;
    bool onTreasure;
    bool openTreasure;

} Player;

// player's functions
void drawPlayer(Player *player, SDL_Renderer *renderer);
void movePlayer(Player *player, const Uint8 *state);
void handlePlayerCollision(Player *player, Map *map);
void meleeAttackPlayer(Player *player, const Uint8 *state, SDL_Renderer *renderer);
void rangedAttackPlayer(Player *player, const Uint8 *state, SDL_Renderer *renderer);
void openTreasurePlayer(Player *player, const Uint8 *state, SDL_Window *window);

#endif