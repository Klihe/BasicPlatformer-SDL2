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
    if (self->isAlive) {
        if (self->faceDirection == FACE_LEFT) {
            self->x -= self->speed;
            if (self->x < self->moveTo) {
                self->faceDirection = FACE_RIGHT;
            }
        } else {
            self->x += self->speed;
            if (self->x > self->moveFrom) {
                self->faceDirection = FACE_LEFT;
            }
        }
    }
}