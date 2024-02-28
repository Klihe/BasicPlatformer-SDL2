#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include "config_entity.h"

typedef struct Enemy {
    int x;
    int y;
    int width;
    int height;
    SDL_Rect rect;

    bool isAlive;
    int health;

    enum FaceDirection faceDirection;

    bool seePlayer;
    bool isMoving;
    bool isSprinting;
    int defaultSpeed;
    float speedMultiplier;
    int speed;
        
    int moveFrom;
    int moveTo;

    bool attackActive;
    int attackTimer;
    int attackCooldown;
    int attackDuration;
} Enemy;

Enemy createEnemy(int x, int y, int width, int height, int speed, int moveFrom, int moveTo);
void drawEnemy(Enemy* enemy, SDL_Renderer* renderer, SDL_Texture* texture_left, SDL_Texture* texture_right);
void moveEnemy(Enemy* enemy, int playerX, int playerY);
void checkEnemy(Enemy* enemy);

#endif // ENEMY_H
