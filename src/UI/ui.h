#ifndef UI_H
#define UI_H

#include <SDL.h>
#include <stdbool.h>

#include "../interaction/interaction.h"

void healthBar(SDL_Renderer* renderer, int health);
bool button(SDL_Renderer* renderer, Uint32 mouse_state, int size[2], int position[2], SDL_Texture* texture);

#endif // UI_H