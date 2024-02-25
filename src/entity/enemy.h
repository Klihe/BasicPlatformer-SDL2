#ifndef ENEMY_H
#define ENEMY_H

#include "config_entity.h"

typedef struct Enemy {
    int x;
    int y;

    int width;
    int height;

    bool isAlive;
    int health;

    int colorR;
    int colorG;
    int colorB;
    int colorA;

    enum FaceDirection faceDirection;

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
void drawEnemy(Enemy* enemy, SDL_Renderer* renderer);
void moveEnemy(Enemy* enemy, int playerX, int playerY);

#endif // ENEMY_H
