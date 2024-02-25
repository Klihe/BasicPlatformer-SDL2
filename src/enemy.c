#include "enemy.h"

// draw enemy
void drawEnemy(Enemy* enemy, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, enemy->color.r, enemy->color.g, enemy->color.b, enemy->color.a);
    SDL_RenderFillRect(renderer, &enemy->rect);
}

// move enemy
void moveEnemy(Enemy* enemy, int playerX, int playerY) {
    if (enemy->isAlive) {
        if (enemy->faceEnemyDirection == ENEMY_FACE_LEFT) {
            enemy->rect.x -= enemy->speed;
            if (enemy->rect.x < enemy->moveTo) {
                enemy->faceEnemyDirection = ENEMY_FACE_RIGHT;
            }
        } else {
            enemy->rect.x += enemy->speed;
            if (enemy->rect.x > enemy->moveFrom) {
                enemy->faceEnemyDirection = ENEMY_FACE_LEFT;
            }
        }
    }
}