#ifndef PLAYER_H
#define PLAYER_H

#include "config_entity.h"
#include "../interaction/interaction.h"

typedef struct Player {
    int x;
    int y;
    int prevX;
    int prevY;
    int width;
    int height;
    SDL_Rect rect;

    enum FaceDirection faceDirection;
    enum Location location;

    bool isFalling;
    int fallingSpeed;

    int defaultSpeed;
    float speedMultiplier;
    int speed;

    SDL_Scancode upKey;
    SDL_Scancode downKey;
    SDL_Scancode leftKey;
    SDL_Scancode rightKey;
    SDL_Scancode sprintKey;

    SDL_Scancode attack1Key;
    SDL_Scancode attack2Key;

    SDL_Scancode interactKey;

    bool onLadder;
    bool onLadderDown;

    bool onChest;
    bool onOpenChest;

    bool attack1Active;
    int attack1Damage;
    int attack1Timer;
    int attack1Cooldown;
    int attack1Duration;
    SDL_Rect attack1Rect;

    bool attack2Active;
    int attack2Damage;
    int attack2Timer;
    int attack2Cooldown;
    int attack2Duration;
    SDL_Rect attack2Rect_left;
    SDL_Rect attack2Rect_right;
} Player;
 
Player createPlayer(int x, int y, int width, int height, int speed);
void drawPlayer(Player* self, SDL_Renderer* renderer, SDL_Texture* texture);
void movePlayer(Player* self, const Uint8* state);
void openChestPlayer(Player* self, const Uint8* state, SDL_Renderer* renderer);
void handlePlayerCollision(Player* self, Map* map);
void attack1Player(Player* self, const Uint8* state, SDL_Renderer* renderer, Uint32 time);
void attack2Player(Player* self, const Uint8* state, SDL_Renderer* renderer, Uint32 time);
void updatePlayer(Player* self);

#endif // PLAYER_H
