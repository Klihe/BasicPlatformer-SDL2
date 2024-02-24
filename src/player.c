#include "player.h"

void drawPlayer(Player* player, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, player->color.r, player->color.g, player->color.b, player->color.a);
    SDL_RenderFillRect(renderer, &player->rect);
}

void movePlayer(Player* player, const Uint8* state) {
    player->prevX = player->rect.x;
    player->prevY = player->rect.y;
    if (state[player->leftKey] && player->rect.x > 0)
        player->rect.x -= player->speed;
    if (state[player->rightKey] && player->rect.x < WINDOW_WIDTH - player->rect.w)
        player->rect.x += player->speed;
    if (state[player->upKey] && player->ladder == true)
        player->rect.y -= player->speed;
    if (state[player->downKey] && player->rect.y < WINDOW_HEIGHT - player->rect.h)
        player->rect.y += player->speed;
}

void handlePlayerCollision(Player* player, Map* map) {
    player->ladder = false; // Set ladder to false initially
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            if (map->tiles[j][i]) {
                SDL_Rect tileRect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                if (player->rect.x < tileRect.x + tileRect.w &&
                    player->rect.x + player->rect.w > tileRect.x &&
                    player->rect.y < tileRect.y + tileRect.h &&
                    player->rect.y + player->rect.h > tileRect.y) {
                    if (map->tiles[j][i] == 1){
                        player->rect.x = player->prevX;
                        player->rect.y = player->prevY;
                    }
                    if (map->tiles[j][i] == 2){
                        player->ladder = true;
                    }
                }
            }
        }
    }
}