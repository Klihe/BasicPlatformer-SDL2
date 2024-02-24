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
    if (state[player->leftKey] && player->rect.x > 0) {
        player->rect.x -= player->speed * player->speedMultiplier;
        player->faceDirection = FACE_LEFT;
    }
    if (state[player->rightKey] && player->rect.x < WINDOW_WIDTH - player->rect.w) {
        player->rect.x += player->speed * player->speedMultiplier;
        player->faceDirection = FACE_RIGHT;
    }

    // ladder movement
    if (state[player->upKey] && player->ladder == true)
        player->rect.y -= player->speed * player->speedMultiplier;
    if (state[player->downKey] && (player->ladder == true || player->ladderDown == true))
        player->rect.y += player->speed * player->speedMultiplier;
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
                if (map->tiles[j][i] == TILE_SOLID){
                    player->rect.x = player->prevX;
                    player->rect.y = player->prevY;
                    // player->fall = false;
                }
                // ladder tile
                else if (map->tiles[j][i] == TILE_LADDER){
                    player->ladder = true;
                }
                // ladder down tile
                else if (map->tiles[j][i] == TILE_LADDER_DOWN){
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

void meleeAttackPlayer(Player* player, const Uint8* state, SDL_Renderer* renderer) {
    SDL_Rect meleeAttackRect = {player->rect.x - 40, player->rect.y, player->rect.w + 80, player->rect.h};
    if (state[player->meleeAttackKey] && SDL_GetTicks() - player->meleeAttackTime > 2000) {
        player->meleeAttackActive = true;
        player->meleeAttackTime = SDL_GetTicks();
        player->speedMultiplier = 0.5;
    }
    else if (player->meleeAttackActive) {
        SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
        SDL_RenderFillRect(renderer, &meleeAttackRect);
        if (SDL_GetTicks() - player->meleeAttackTime > 1000) {
            player->meleeAttackActive = false;
            player->speedMultiplier = 1;
        }
    }
}

void rangedAttackPlayer(Player* player, const Uint8* state, SDL_Renderer* renderer) {
    SDL_Rect rangedAttackRectLeft = {0, player->rect.y + 20, player->rect.x, player->rect.h - 40};
    SDL_Rect rangedAttackRectRight = {player->rect.x, player->rect.y + 20, WINDOW_WIDTH-player->rect.x, player->rect.h - 40};
    if (state[player->rangedAttackKey] && SDL_GetTicks() - player->rangedAttackTime > 2000) {
        player->rangedAttackActive = true;
        player->rangedAttackTime = SDL_GetTicks();
        player->speedMultiplier = 0.5;
    }
    else if (player->rangedAttackActive) {
        SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
        if (player->faceDirection == FACE_RIGHT) {
            SDL_RenderFillRect(renderer, &rangedAttackRectRight);
        }
        else if (player->faceDirection == FACE_LEFT) {
            SDL_RenderFillRect(renderer, &rangedAttackRectLeft);
        }
        if (SDL_GetTicks() - player->rangedAttackTime > 1000) {
            player->rangedAttackActive = false;
            player->speedMultiplier = 1;
        }
    }
}