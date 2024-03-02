#include "map.h"

// draw map
void drawMap(Map* map, SDL_Renderer* renderer, SDL_Texture* ladder, SDL_Texture* solid, SDL_Texture* foward, SDL_Texture* backward, SDL_Texture* treasure, SDL_Texture* lava) {
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            switch (map->tiles[j][i]) {
                case TILE_EMPTY:
                    break;
                case TILE_SOLID:
                    SDL_RenderCopy(renderer, solid, NULL, &(SDL_Rect){i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE});
                    break;
                case TILE_LADDER_DOWN:
                    break;
                case TILE_LADDER:
                    SDL_RenderCopy(renderer, ladder, NULL, &(SDL_Rect){i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE});
                    break;
                case TILE_TREAUSURE:
                    SDL_RenderCopy(renderer, treasure, NULL, &(SDL_Rect){i * TILE_SIZE, j * TILE_SIZE + 7*4, 16*4, 13*4});
                    break;
                case TILE_PORTAL_FOWARD:
                    SDL_RenderCopy(renderer, foward, NULL, &(SDL_Rect){i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE});
                    break;
                case TILE_PORTAL_BACKWARD:
                    SDL_RenderCopy(renderer, backward, NULL, &(SDL_Rect){i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE});
                    break;
                case TILE_LAVA:
                    SDL_RenderCopy(renderer, lava, NULL, &(SDL_Rect){i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE});
                    break;
            }
        }
    }
}

void getInfoMap();
