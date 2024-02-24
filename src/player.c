#include "player.h"

// draw player
void drawPlayer(Player* player, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, player->color.r, player->color.g, player->color.b, player->color.a);
    SDL_RenderFillRect(renderer, &player->rect);
}

// move player
void movePlayer(Player* player, const Uint8* state) {
    // save previous position
    player->prevX = player->rect.x;
    player->prevY = player->rect.y;

    // left and right movement
    if (state[player->leftKey] && player->rect.x > 0)
        player->rect.x -= player->speed;
    if (state[player->rightKey] && player->rect.x < WINDOW_WIDTH - player->rect.w)
        player->rect.x += player->speed;

    // ladder movement
    if (state[player->upKey] && player->ladder == true)
        player->rect.y -= player->speed;
    if (state[player->downKey] && (player->ladder == true || player->ladderDown == true))
        player->rect.y += player->speed;
}

// handle player collision
void handlePlayerCollision(Player* player, Map* map) {
    // default state
    player->ladder = false;
    player->ladderDown = false;

    // check collision with map tiles
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            SDL_Rect tileRect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            if (player->rect.x < tileRect.x + tileRect.w &&
                player->rect.x + player->rect.w > tileRect.x &&
                player->rect.y < tileRect.y + tileRect.h &&
                player->rect.y + player->rect.h > tileRect.y) {
                // solid tile
                if (map->tiles[j][i] == 1){
                    player->rect.x = player->prevX;
                    player->rect.y = player->prevY;
                    // player->fall = false;
                }
                // ladder tile
                else if (map->tiles[j][i] == 2){
                    player->ladder = true;
                }
                // ladder down tile
                else if (map->tiles[j][i] == 3){
                    player->ladderDown = true;
                }
            }
            // else if (map->tiles[j][i] == 0 && map->tiles[j+1][i] == 0) {
            //     if (!player->fall && (player->rect.x >= tileRect.x &&
            //         player->rect.y >= tileRect.y &&
            //         player->rect.x + player->rect.w <= tileRect.x + tileRect.w &&
            //         player->rect.y + player->rect.h <= tileRect.y + tileRect.h)) {
            //         player->fall = true;
            //     }
            //     if (player->fall) {
            //         player->rect.y += player->speed;
            //     }
            // }
        }
    }
}