#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>

#include "config.h"
enum FaceEnemyDirection {
    ENEMY_FACE_LEFT,
    ENEMY_FACE_RIGHT
};

typedef struct Enemy {
    SDL_Rect rect;
    SDL_Color color;

    int moveFrom;
    int moveTo;

    enum FaceEnemyDirection faceEnemyDirection;
    int speed;

    int health;
    int damage;
    int isAlive;
} Enemy;

void drawEnemy(Enemy *enemy, SDL_Renderer *renderer);
void moveEnemy(Enemy *enemy, int playerX, int playerY);

#endif