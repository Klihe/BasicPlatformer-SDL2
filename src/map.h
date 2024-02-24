#ifndef MAP_H
#define MAP_H

// include libraries
#include <SDL.h>

// include files
#include "config.h"

enum TileType{
    TILE_EMPTY,
    TILE_SOLID,
    TILE_LADDER,
    TILE_LADDER_DOWN,
    TILE_TREAUSURE
};

// define map struct
typedef struct {
    enum TileType tiles[MAP_HEIGHT][MAP_WIDTH];
} Map;


// map's functions
void drawMap(Map *map, SDL_Renderer* renderer);

#endif