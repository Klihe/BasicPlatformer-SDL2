#include "ui.h"

void healthBar(SDL_Renderer* renderer, int health) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect healthBarBackground = {10, 10, 200, 20};
    SDL_RenderFillRect(renderer, &healthBarBackground);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect healthBar = {10, 10, 200 * health / 100, 20};
    SDL_RenderFillRect(renderer, &healthBar);
}

bool button(SDL_Renderer* renderer, Uint32 mouse_state, int size[2], int position[2], SDL_Texture* texture) {
    SDL_Rect button = {position[0], position[1], size[0], size[1]};
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_RenderCopy(renderer, texture, NULL, &button);
    if (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        SDL_SetTextureColorMod(texture, 150, 150, 150);
        SDL_RenderFillRect(renderer, &button);
        if (pointRectCollision(x, y, &button)) {
            return true;
        } else {
            return false;
        }
    } else {
        if (pointRectCollision(x, y, &button)) {
            SDL_SetTextureColorMod(texture, 200, 200, 200);
        } else {
            SDL_SetTextureColorMod(texture, 255, 255, 255);
        }
        return false;
    }
}