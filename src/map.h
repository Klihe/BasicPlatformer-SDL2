#ifndef MAP_H
#define MAP_H

// include libraries
#include <SDL.h>

// include files
#include "config.h"

// define tile types
enum TileType{
    TILE_EMPTY,
    TILE_SOLID,
    TILE_LADDER,
    TILE_LADDER_DOWN,
    TILE_TREAUSURE,
    TILE_PORTAL_FOWARD,
    TILE_PORTAL_BACKWARD
};

// define map struct
typedef struct {
    enum TileType tiles[MAP_HEIGHT][MAP_WIDTH];
} Map;


// map's functions
void drawMap(Map *map, SDL_Renderer* renderer, SDL_Texture* texture_block_ladder, SDL_Texture* texture_block_solid, SDL_Texture* texture_block_foward, SDL_Texture* texture_block_backward, SDL_Texture* texture_block_treasure);

#endif