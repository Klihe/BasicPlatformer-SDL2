#include "enemy.h"

Enemy createEnemy(int x, int y, int width, int height, int speed, int moveFrom, int moveTo) {
    Enemy self;
    self.width = width;
    self.height = height;
    self.x = x * TILE_SIZE + self.width;
    self.y = y * TILE_SIZE - self.height;
    self.rect = (SDL_Rect){self.x, self.y, self.width, self.height};

    self.isAlive = true;
    self.health = 20;

    self.faceDirection = FACE_LEFT;

    self.seePlayer = false;
    self.isMoving = false;
    self.isSprinting = false;
    self.defaultSpeed = speed;
    self.speedMultiplier = 1;
    self.speed = self.defaultSpeed * self.speedMultiplier;

    self.frame = 0;
    self.frameDelay = 100;
    self.frameNext = 0;

    self.moveFrom = moveFrom * TILE_SIZE + self.width;
    self.moveTo = moveTo * TILE_SIZE;

    self.attackActive = false;
    self.attackDamage = 20;
    self.attackTimer = 0;
    self.attackCooldown = 2000;
    self.attackDuration = 1;
    self.attackRect = (SDL_Rect){0, 0, 0, 0};

    return self;
}

void drawEnemy(Enemy* self, SDL_Renderer* renderer, SDL_Texture** texture, Uint32 time) {
    if (self->isMoving) {
        if (time > self->frameNext) {
            self->frame = (self->frame + 1) % 4;
            self->frameNext = time + self->frameDelay;
        }
        if (self->faceDirection == FACE_LEFT) {
            SDL_RenderCopy(renderer, texture[self->frame], NULL, &self->rect);
        }
        else if (self->faceDirection == FACE_RIGHT) {
            SDL_RenderCopyEx(renderer, texture[self->frame], NULL, &self->rect, 0, NULL, SDL_FLIP_HORIZONTAL);
        }
    } else {
        if (self->faceDirection == FACE_LEFT) {
            SDL_RenderCopy(renderer, texture[0], NULL, &self->rect);
        }
        else if (self->faceDirection == FACE_RIGHT) {
            SDL_RenderCopyEx(renderer, texture[0], NULL, &self->rect, 0, NULL, SDL_FLIP_HORIZONTAL);
        }
    }
}

void moveEnemy(Enemy* self, int playerX, int playerY) {
    if (self->isAlive) {
        self->isMoving = true;
        self->speed = self->defaultSpeed * self->speedMultiplier;
        if (self->seePlayer && self->y < playerY + 40 && self->y > playerY - 40) {
            if (self->x < playerX - 40 && self->moveFrom > playerX) {
                self->speedMultiplier = 2;
                self->x += self->speed;
            } else if (self->x > playerX + 40 && self->moveTo < playerX) {
                self->speedMultiplier = 2;
                self->x -= self->speed;
            } else {
                attackEnemy(self, SDL_GetTicks());
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

void attackEnemy(Enemy* self, Uint32 time) {
    self->attackRect = (SDL_Rect){self->x - self->width, self->y, self->width * 3, self->height};
    if (time - self->attackTimer > self->attackCooldown) {
        self->attackActive = true;
        self->attackTimer = time;
        self->speedMultiplier = 0.5;
    }
    else if (self->attackActive) {
        self->attackActive = false;
        self->speedMultiplier = 1;
    }
}

void updateEnemy(Enemy* self) {
    self->rect = (SDL_Rect){self->x, self->y, self->width, self->height};
    if (self->health <= 0) {
        self->isAlive = false;
    }
}