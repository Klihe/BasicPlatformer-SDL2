#ifndef MAP_H
#define MAP_H

#include <SDL.h>

#define MAP_WIDTH 16
#define MAP_HEIGHT 9
#define TILE_SIZE 80

typedef struct {
    int tiles[MAP_HEIGHT][MAP_WIDTH];
} Map;

void drawMap(Map *map, SDL_Renderer* renderer);

#endif