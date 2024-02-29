#include "player.h"

Player createPlayer(int x, int y, int width, int height, int speed) {
    Player self;
    self.x = x;
    self.y = y;
    self.prevX = self.x;
    self.prevY = self.y;
    self.width = width;
    self.height = height;
    self.rect = (SDL_Rect){self.x, self.y, self.width, self.height};

    self.isAlive = true;
    self.health = 100;

    self.faceDirection = FACE_RIGHT;
    self.location = MAP1;

    self.isFalling = true;
    self.isJumping = false;
    self.jumpSpeed = 10;
    self.isMoving = false;
    self.fallingSpeed = 0;
    self.defaultSpeed = speed;
    self.speedMultiplier = 1;
    self.speed = self.defaultSpeed * self.speedMultiplier;

    self.frame = 0;
    self.frameDelay = 100;
    self.frameNext = 0;

    self.upKey = SDL_SCANCODE_W;
    self.downKey = SDL_SCANCODE_S;
    self.leftKey = SDL_SCANCODE_A;
    self.rightKey = SDL_SCANCODE_D;
    self.sprintKey = SDL_SCANCODE_LSHIFT;
    self.jumpKey = SDL_SCANCODE_SPACE;

    self.attack1Key = SDL_SCANCODE_E;
    self.attack2Key = SDL_SCANCODE_Q;
    self.interactKey = SDL_SCANCODE_F;

    self.onLadder = false;
    self.onLadderDown = false;
    self.onChest = false;
    self.onOpenChest = false;

    self.attack1Active = false;
    self.attack1Damage = 5;
    self.attack1Timer = 0;
    self.attack1Cooldown = 500;
    self.attack1Duration = 1;
    self.attack1Rect = (SDL_Rect){0, 0, 0, 0};

    self.attack2Active = false;
    self.attack2Damage = 5; 
    self.attack2Timer = 0;
    self.attack2Cooldown = 1000;
    self.attack2Duration = 1;
    self.attack2Rect_left = (SDL_Rect){0, 0, 0, 0};
    self.attack2Rect_right = (SDL_Rect){0, 0, 0, 0};

    return self;
};

void drawPlayer(Player* self, SDL_Renderer* renderer, SDL_Texture** texture, Uint32 time) {
    if (self->isMoving && self->isAlive) {
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
    } else if (self->isAlive) {
        if (self->faceDirection == FACE_LEFT) {
            SDL_RenderCopy(renderer, texture[0], NULL, &self->rect);
        }
        else if (self->faceDirection == FACE_RIGHT) {
            SDL_RenderCopyEx(renderer, texture[0], NULL, &self->rect, 0, NULL, SDL_FLIP_HORIZONTAL);
        }
    }
}

void movePlayer(Player* self, const Uint8* state) {
    self->prevX = self->x;
    self->prevY = self->y;
    self->speed = self->defaultSpeed * self->speedMultiplier;
    self->isMoving = false;

    if (state[self->sprintKey] && !(state[self->upKey] && self->onLadder) && !(state[self->downKey] && self->onLadder)) {
        self->speedMultiplier = 1.5;
    } else {
        self->speedMultiplier = 1;
    }
    if (!self->isJumping) {
        if (state[self->jumpKey]) {
            self->isJumping = true;
            self->jumpSpeed = 20;
        }
    } else {
        if (self->jumpSpeed >= -5) {
            self->y -= (self->jumpSpeed * abs(self->jumpSpeed)) * 0.025;
            self->jumpSpeed -= 1;
        } else {
            self->jumpSpeed = 5;
            self->isJumping = false;
        }
    }
    if (state[self->leftKey] && self->x > 0) {
        self->x -= self->speed;
        self->faceDirection = FACE_LEFT;
        self->isMoving = true;
    }
    if (state[self->rightKey] && self->x < WINDOW_WIDTH - self->width) {
        self->x += self->speed;
        self->faceDirection = FACE_RIGHT;
        self->isMoving = true;
    }
    if (state[self->upKey] && self->onLadder == true) {
        self->y -= self->speed;
        self->speedMultiplier = 0.75;
        self->isMoving = true;
    }
    if (state[self->downKey] && (self->onLadder == true || self->onLadderDown == true)) {
        self->y += self->speed;
        self->speedMultiplier = 0.5;
        self->isMoving = true;
    }
}

void openChestPlayer(Player* self, const Uint8* state, SDL_Renderer* renderer) {
    SDL_Rect rect = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 100, 200, 200};
    if (state[self->interactKey] && self->onChest) {
        SDL_Delay(100);
        if (!self->onOpenChest) {
            self->onOpenChest = true;
        }
        else {
            self->onOpenChest = false;
        }
    } 
    if (self->onOpenChest && self->onChest) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void handlePlayerCollision(Player* self, Map* map) {
    self->onLadder = false;
    self->onLadderDown = false;
    self->onChest = false;
    self->isFalling = true;

    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            SDL_Rect tileRect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            if (self->x < tileRect.x + tileRect.w &&
                self->x + self->width > tileRect.x &&
                self->y < tileRect.y + tileRect.h &&
                self->y + self->height > tileRect.y) {
                if (map->tiles[j][i] == TILE_SOLID){
                    self->isFalling = false;
                    self->fallingSpeed = 0;
                    int result = getCollisionValue(&self->rect, &tileRect);
                    self->isFalling = !result;
                    if (result > 20) {
                        self->y = self->prevY;
                        self->x = self->prevX;
                    }
                    else if (result > 1) {
                        self->y -= result-1;
                        self->x = self->prevX;
                    }
                }
                else if (map->tiles[j][i] == TILE_LADDER){
                    self->fallingSpeed = 0;
                    self->isFalling = false;
                    self->onLadder = true;
                }
                else if (map->tiles[j][i] == TILE_LADDER_DOWN){
                    self->isFalling = true;
                    self->onLadderDown = true;
                }
                else if (map->tiles[j][i] == TILE_TREAUSURE){
                    self->fallingSpeed = 0;
                    self->onChest = true;
                    self->isFalling = false;
                }
                else if (map->tiles[j][i] == TILE_PORTAL_FOWARD){
                    self->fallingSpeed = 0;
                    self->isFalling = false;
                    self->location = self->location +1;
                    self->x = 0;
                    self->y = WINDOW_HEIGHT - 140;
                }
                else if (map->tiles[j][i] == TILE_PORTAL_BACKWARD){
                    self->fallingSpeed = 0;
                    self->isFalling = false;
                    self->location = self->location -1;
                    self->x = WINDOW_WIDTH - 40;
                    self->y = WINDOW_HEIGHT - 140;
                }
            }
        }
    }
    if (self->isFalling) {
        self->fallingSpeed += 1;
        self->y += self->fallingSpeed;
    }
}

void attack1Player(Player* self, const Uint8* state, SDL_Renderer* renderer, Uint32 time) {
    self->attack1Rect = (SDL_Rect){self->x - self->width, self->y, self->width * 3, self->height};
    if (state[self->attack1Key] && time - self->attack1Timer > self->attack1Cooldown) {
        self->attack1Active = true;
        self->attack1Timer = time;
        self->speedMultiplier = 0.5;
    }
    else if (self->attack1Active) {
        SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
        SDL_RenderFillRect(renderer, &self->attack1Rect);
        if (time - self->attack1Timer > self->attack1Duration) {
            self->attack1Active = false;
            self->speedMultiplier = 1;
        }
    }
}

void attack2Player(Player* self, const Uint8* state, SDL_Renderer* renderer, Uint32 time) {
    self->attack2Rect_left = (SDL_Rect){0, self->y + self->height/3, self->x, self->height - self->width};
    self->attack2Rect_right = (SDL_Rect){self->x + self->width, self->y + self->height/3, WINDOW_WIDTH - self->x, self->height - self->width};
    if (state[self->attack2Key] && time - self->attack2Timer > self->attack2Cooldown) {
        self->attack2Active = true;
        self->attack2Timer = time;
        self->speedMultiplier = 0.5;
    }
    else if (self->attack2Active) {
        SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
        if (self->faceDirection == FACE_LEFT)
            SDL_RenderFillRect(renderer, &self->attack2Rect_left);
        else if (self->faceDirection == FACE_RIGHT)
            SDL_RenderFillRect(renderer, &self->attack2Rect_right);
        if (time - self->attack2Timer > self->attack2Duration) {
            self->attack2Active = false;
            self->speedMultiplier = 1;
        }
    }
}

void updatePlayer(Player* self) {
    self->rect = (SDL_Rect){self->x, self->y, self->width, self->height};
    if (self->health <= 0) {
        self->isAlive = false;
    }
}