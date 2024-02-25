#include "player.h"

Player createPlayer(int x, int y, int width, int height, int speed) {
    Player self;
    self.x = x;
    self.y = y;
    self.prevX = self.x;
    self.prevY = self.y;

    self.width = width;
    self.height = height;
    self.defaultWidth = self.width;
    self.defaultHeight = self.height;

    self.colorR = 255;
    self.colorG = 0;
    self.colorB = 0;
    self.colorA = 255;

    self.faceDirection = FACE_RIGHT;
    self.location = MAP1;

    self.isMoving = false;
    self.isSprinting = false;
    self.defaultSpeed = speed;
    self.speedMultiplier = 1;
    self.speed = self.defaultSpeed * self.speedMultiplier;

    self.upKey = SDL_SCANCODE_W;
    self.downKey = SDL_SCANCODE_S;
    self.leftKey = SDL_SCANCODE_A;
    self.rightKey = SDL_SCANCODE_D;
    self.sprintKey = SDL_SCANCODE_LSHIFT;

    self.attack1Key = SDL_SCANCODE_E;
    self.attack2Key = SDL_SCANCODE_Q;

    self.interactKey = SDL_SCANCODE_SPACE;

    self.onLadder = false;
    self.onLadderDown = false;
    
    self.onChest = false;
    self.onOpenChest = false;

    self.attack1Active = false;
    self.attack1Timer = 0;
    self.attack1Cooldown = 500;
    self.attack1Duration = 100;

    self.attack2Active = false; 
    self.attack2Timer = 0;
    self.attack2Cooldown = 1000;
    self.attack2Duration = 100;

    return self;
};

void drawPlayer(Player* self, SDL_Renderer* renderer) {
    SDL_Rect rect = {self->x, self->y, self->width, self->height};
    SDL_SetRenderDrawColor(renderer, self->colorR, self->colorG, self->colorB, self->colorA);
    SDL_RenderFillRect(renderer, &rect);
}

void movePlayer(Player* self, const Uint8* state) {
    self->prevX = self->x;
    self->prevY = self->y;
    self->speed = self->defaultSpeed * self->speedMultiplier;

    if (state[self->sprintKey] && !state[self->downKey]) {
        self->speedMultiplier = 2;
        if (self->height != 80) {
            self->y -= 20;
            self->height = 80;
        }
    } else {
        self->speedMultiplier = 1;
        if (self->height != 60) {
            self->y += 20;
            self->height = 60;
        }
    }
    if (state[self->leftKey] && self->x > 0) {
        self->x -= self->speed;
        self->faceDirection = FACE_LEFT;
    }
    if (state[self->rightKey] && self->x < WINDOW_WIDTH - self->width) {
        self->x += self->speed;
        self->faceDirection = FACE_RIGHT;
    }
    if (state[self->upKey] && self->onLadder == true)
        self->y -= self->speed;
    if (state[self->downKey] && (self->onLadder == true || self->onLadderDown == true))
        self->y += self->speed;
}

void openChestPlayer(Player* self, const Uint8* state, SDL_Window* window) {
    if (state[self->interactKey] && self->onChest == true && !self->onOpenChest) {
        SDL_ShowWindow(window);
        self->onOpenChest = true;
        SDL_Delay(100);
    }
    else if (state[self->interactKey] && self->onOpenChest) {
        SDL_HideWindow(window);
        self->onOpenChest = false;
        SDL_Delay(100);
    }
}

void handlePlayerCollision(Player* self, Map* map) {
    self->onLadder = false;
    self->onLadderDown = false;
    self->onChest = false;

    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            SDL_Rect tileRect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            if (self->x < tileRect.x + tileRect.w &&
                self->x + self->width > tileRect.x &&
                self->y < tileRect.y + tileRect.h &&
                self->y + self->height > tileRect.y) {
                if (map->tiles[j][i] == TILE_SOLID){
                    self->x = self->prevX;
                    self->y = self->prevY;
                }
                else if (map->tiles[j][i] == TILE_LADDER){
                    self->onLadder = true;
                }
                else if (map->tiles[j][i] == TILE_LADDER_DOWN){
                    self->onLadderDown = true;
                }
                else if (map->tiles[j][i] == TILE_TREAUSURE){
                    self->onChest = true;
                }
                else if (map->tiles[j][i] == TILE_PORTAL_FOWARD){
                    self->location = self->location +1;
                    self->x = 0;
                    self->y = WINDOW_HEIGHT - 140;
                }
                else if (map->tiles[j][i] == TILE_PORTAL_BACKWARD){
                    self->location = self->location -1;
                    self->x = WINDOW_WIDTH - 40;
                    self->y = WINDOW_HEIGHT - 140;
                }
            }
        }
    }
}

void attack1Player(Player* self, const Uint8* state, SDL_Renderer* renderer, Uint32 time) {
    SDL_Rect rect = {self->x - self->width, self->y, self->width * 3, self->height};
    if (state[self->attack1Key] && time - self->attack1Timer > self->attack1Cooldown) {
        self->attack1Active = true;
        self->attack1Timer = time;
        self->speedMultiplier = 0.5;
    }
    else if (self->attack1Active) {
        SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
        if (time - self->attack1Timer > self->attack1Duration) {
            self->attack1Active = false;
            self->speedMultiplier = 1;
        }
    }
}

void attack2Player(Player* self, const Uint8* state, SDL_Renderer* renderer, Uint32 time) {
    SDL_Rect rectLeft = {0, self->y + self->height/3, self->x, self->height - self->width};
    SDL_Rect rectRight = {self->x + self->width, self->y + self->height/3, WINDOW_WIDTH - self->x, self->height - self->width};
    if (state[self->attack2Key] && time - self->attack2Timer > self->attack2Cooldown) {
        self->attack2Active = true;
        self->attack2Timer = time;
        self->speedMultiplier = 0.5;
    }
    else if (self->attack2Active) {
        SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
        if (self->faceDirection == FACE_LEFT)
            SDL_RenderFillRect(renderer, &rectLeft);
        else if (self->faceDirection == FACE_RIGHT)
            SDL_RenderFillRect(renderer, &rectRight);
        if (time - self->attack2Timer > self->attack2Duration) {
            self->attack2Active = false;
            self->speedMultiplier = 1;
        }
    }
}