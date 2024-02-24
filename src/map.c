#include "map.h"

// draw map
void drawMap(Map* map, SDL_Renderer* renderer) {
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            if (map->tiles[j][i] == TILE_SOLID) {
                SDL_Rect rect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
            if (map->tiles[j][i] == TILE_LADDER) {
                SDL_Rect rect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
            if (map->tiles[j][i] == TILE_LADDER_DOWN) {
                SDL_Rect rect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
            if (map->tiles[j][i] == TILE_TREAUSURE) {
                SDL_Rect rect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
            if (map->tiles[j][i] == TILE_PORTAL_FOWARD) {
                SDL_Rect rect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
            if (map->tiles[j][i] == TILE_PORTAL_BACKWARD) {
                SDL_Rect rect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_SetRenderDrawColor(renderer, 100, 0, 100, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}
