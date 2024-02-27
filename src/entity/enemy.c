#include "enemy.h"

Enemy createEnemy(int x, int y, int width, int height, int speed, int moveFrom, int moveTo) {
    Enemy self;
    self.width = width;
    self.height = height;

    self.x = x * TILE_SIZE + self.width;
    self.y = y * TILE_SIZE - self.height;

    self.isAlive = true;
    self.health = 100;

    self.colorR = 0;
    self.colorG = 0;
    self.colorB = 255;
    self.colorA = 255;

    self.faceDirection = FACE_LEFT;

    self.seePlayer = false;
    self.isMoving = false;
    self.isSprinting = false;
    self.defaultSpeed = speed;
    self.speedMultiplier = 1;
    self.speed = self.defaultSpeed * self.speedMultiplier;

    self.moveFrom = moveFrom * TILE_SIZE + self.width;
    self.moveTo = moveTo * TILE_SIZE;

    self.attackActive = false;
    self.attackTimer = 0;
    self.attackCooldown = 2000;
    self.attackDuration = 1000;

    return self;
}

void drawEnemy(Enemy* self, SDL_Renderer* renderer) {
    SDL_Rect rect = {self->x, self->y, self->width, self->height};
    SDL_SetRenderDrawColor(renderer, self->colorR, self->colorG, self->colorB, self->colorA);
    SDL_RenderFillRect(renderer, &rect);
}

void moveEnemy(Enemy* self, int playerX, int playerY) {
    self->speed = self->defaultSpeed * self->speedMultiplier;
    if (self->isAlive) {
        if (self->seePlayer && self->y < playerY + 40 && self->y > playerY - 40) {
            if (self->x < playerX - 40 && self->moveFrom > playerX) {
                self->speedMultiplier = 2;
                self->x += self->speed;
            } else if (self->x > playerX + 40 && self->moveTo < playerX) {
                self->speedMultiplier = 2;
                self->x -= self->speed;
            } else {
                //printf("attack\n");
            }
        } else {
            self->seePlayer = false;
        }
        if (self->faceDirection == FACE_LEFT && !self->seePlayer) {
            if ((self->y < playerY + 40 && self->y > playerY - 40) && self->x > playerX && self->moveTo < playerX) {
                self->seePlayer = true;
            }
            else if (self->x > self->moveTo) {
                self->speedMultiplier = 1;
                self->x -= self->speed;
            } else {
                self->faceDirection = FACE_RIGHT;
            }
        } else if (self->faceDirection == FACE_RIGHT && !self->seePlayer) {
            if ((self->y < playerY + 40 && self->y > playerY - 40) && self->x < playerX && self->moveFrom > playerX) {
                self->seePlayer = true;
            }
            else if (self->x < self->moveFrom) {
                self->speedMultiplier = 1;
                self->x += self->speed;
            } else {
                self->faceDirection = FACE_LEFT;
            }
        }
    }
}