// main.c

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "config.h"
#include "player.h"
#include "map.h"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Player player = {{WINDOW_WIDTH/2 - 40/2, WINDOW_HEIGHT - 140, 40, 60}, {255, 0, 0, 255}, 5, 0, WINDOW_HEIGHT - 60, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_S,};
    Map map = {{{0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0},
                {0,0,0,3,0,0,0,0,0,2,1,1,1,1,1,0},
                {0,1,1,2,1,0,0,3,0,2,0,3,0,0,0,0},
                {0,0,0,2,0,0,0,2,1,1,1,2,1,0,0,0},
                {0,3,0,2,0,0,0,2,0,0,0,2,0,0,0,0},
                {0,2,1,1,1,1,1,1,0,0,0,2,0,3,0,0},
                {0,2,0,0,0,0,0,0,0,0,0,1,1,2,1,0},
                {0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}};


    SDL_Event event;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
        }
        const Uint8* state = SDL_GetKeyboardState(NULL);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        drawMap(&map, renderer);

        drawPlayer(&player, renderer);
        movePlayer(&player, state);

        handlePlayerCollision(&player, &map);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}