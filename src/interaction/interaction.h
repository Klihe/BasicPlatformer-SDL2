#ifndef INTERACTION_H
#define INTERACTION_H

#include <SDL.h>
#include <stdbool.h>

bool collision(SDL_Rect* a, SDL_Rect* b);
bool allInCollision(SDL_Rect* a, SDL_Rect* b);
int getCollisionValue(SDL_Rect* a, SDL_Rect* b);
int attackCollision(SDL_Rect* a, SDL_Rect* b, bool active, int damage);

#endif // INTERACTION_H