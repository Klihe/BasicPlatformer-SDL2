#include "interaction.h"

bool checkCollision(SDL_Rect* a, SDL_Rect* b) {
    if (a->x + a->w < b->x || a->x > b->x + b->w) {
        return false;
    }
    if (a->y + a->h < b->y || a->y > b->y + b->h) {
        return false;
    }
    return true;
}

bool allInCollision(SDL_Rect* a, SDL_Rect* b) {
    if (a->x < b->x + b->w &&
        a->x + a->w > b->x &&
        a->y < b->y + b->h &&
        a->y + a->h > b->y) {
        return true;
    }
    return false;
}

int getCollisionValue(SDL_Rect* a, SDL_Rect* b) {
    int result = 0;
    if (a->y + a->h > b->y) {
        result = a->y + a->h - b->y;
    }

    return result;
}

int attackCollision(SDL_Rect* a, SDL_Rect* b, bool active, int damage) {
    if (checkCollision(a, b) && active) {
        return damage;
    } else {
        return 0;
    }
}
