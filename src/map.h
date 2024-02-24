#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include "config.h"

typedef struct {
    int tiles[MAP_HEIGHT][MAP_WIDTH];
} Map;

void drawMap(Map *map, SDL_Renderer* renderer);

#endif