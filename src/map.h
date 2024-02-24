#ifndef MAP_H
#define MAP_H

// include libraries
#include <SDL.h>

// include files
#include "config.h"

// define map struct
typedef struct {
    int tiles[MAP_HEIGHT][MAP_WIDTH];
} Map;

// map's functions
void drawMap(Map *map, SDL_Renderer* renderer);

#endif