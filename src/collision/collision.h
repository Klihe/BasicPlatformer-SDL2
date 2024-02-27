#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>
#include <stdbool.h>

bool collision(SDL_Rect* a, SDL_Rect* b);
bool allInCollision(SDL_Rect* a, SDL_Rect* b);
int getCollisionValue(SDL_Rect* a, SDL_Rect* b);

#endif // COLLISION_H