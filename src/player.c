#include "player.h"

void drawPlayer(Player* player, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, player->color.r, player->color.g, player->color.b, player->color.a);
    SDL_RenderFillRect(renderer, &player->rect);
}

void movePlayer(Player* player, const Uint8* state) {
    if (state[player->leftKey] && player->rect.x > 0)
        player->rect.x -= player->speed;
    if (state[player->rightKey] && player->rect.x < WINDOW_WIDTH - player->rect.w)
        player->rect.x += player->speed;
}

void jumpPlayer(Player* player, const Uint8* state) {
    if (state[player->upKey] && player->jumping == false) {
        player->jumping = true;
    }
    if (player->jumping) {
        if (player->jumpStrength >= -15) {
            player->rect.y -= (player->jumpStrength * abs(player->jumpStrength)) * 0.25;
            player->jumpStrength--;
        } else {
            player->rect.y = WINDOW_HEIGHT - player->rect.h;
            player->jumping = false;
            player->jumpStrength = 15;
        }
    }
}