#include "ui.h"

void healthBar(SDL_Renderer* renderer, int health) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect healthBarBackground = {10, 10, 200, 20};
    SDL_RenderFillRect(renderer, &healthBarBackground);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect healthBar = {10, 10, 200 * health / 100, 20};
    SDL_RenderFillRect(renderer, &healthBar);
}