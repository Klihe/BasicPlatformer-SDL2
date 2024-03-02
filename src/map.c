#include "map.h"

// draw map
void drawMap(Map* map, SDL_Renderer* renderer, SDL_Texture* texture_block_ladder, SDL_Texture* texture_block_solid, SDL_Texture* texture_block_foward, SDL_Texture* texture_block_backward, SDL_Texture* texture_block_treasure) {
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            if (map->tiles[j][i] == TILE_SOLID) {
                SDL_RenderCopy(renderer, texture_block_solid, NULL, &(SDL_Rect){i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE});
            }
            if (map->tiles[j][i] == TILE_LADDER) {
                SDL_RenderCopy(renderer, texture_block_ladder, NULL, &(SDL_Rect){i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE});
            }
            // if (map->tiles[j][i] == TILE_LADDER_DOWN) {
            //     SDL_Rect rect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            //     SDL_SetRenderDrawColor(renderer, 0, 100, 0, 0);
            //     SDL_RenderFillRect(renderer, &rect);
            // }
            if (map->tiles[j][i] == TILE_TREAUSURE) {
                SDL_RenderCopy(renderer, texture_block_treasure, NULL, &(SDL_Rect){i * TILE_SIZE, j * TILE_SIZE + 7*4, 16*4, 13*4});
            }
            if (map->tiles[j][i] == TILE_PORTAL_FOWARD) {
                SDL_RenderCopy(renderer, texture_block_foward, NULL, &(SDL_Rect){i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE});
            }
            if (map->tiles[j][i] == TILE_PORTAL_BACKWARD) {
                SDL_RenderCopy(renderer, texture_block_backward, NULL, &(SDL_Rect){i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE});
            }
        }
    }
}

void getInfoMap();
