// include libraries
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

// include files
#include "config.h"
#include "player.h"
#include "map.h"

// main function
int main() {
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // create window
    SDL_Window* window_main = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Window* window_treasure = SDL_CreateWindow("SDL Treasure", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_HIDDEN);
    if (window_main == NULL || window_treasure == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // create renderer
    SDL_Renderer* renderer_main = SDL_CreateRenderer(window_main, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Renderer* renderer_treasure = SDL_CreateRenderer(window_treasure, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer_main == NULL || renderer_treasure == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window_main);
        SDL_DestroyWindow(window_treasure);
        SDL_Quit();
        return 1;
    }

    // create player and map
    Player player = {{WINDOW_WIDTH/2 - 40/2, WINDOW_HEIGHT - 140, 40, 60}, {255, 0, 0, 255}, MAP1, 5, 1, 0, WINDOW_HEIGHT - 60, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_LSHIFT, SDL_SCANCODE_E, SDL_SCANCODE_Q, SDL_SCANCODE_SPACE, false};
    Map map1 = {{{0,0,0,0,0,0,0,0,0,3,0,0,0,5,0,0},
                {0,4,0,3,0,0,0,0,0,2,1,1,1,1,1,0},
                {0,1,1,2,1,0,0,3,0,2,0,3,0,0,0,0},
                {0,0,0,2,0,0,0,2,1,1,1,2,1,0,0,0},
                {0,3,0,2,0,0,0,2,0,0,0,2,0,0,0,0},
                {0,2,1,1,1,1,1,1,0,0,0,2,0,3,0,0},
                {0,2,0,0,0,0,0,0,0,0,0,1,1,2,1,0},
                {0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}};
    Map map2 = {{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}};

    // game loop
    SDL_Event event;
    bool quit = false;
    while (!quit){
        // handle events
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
        }

        // handle player input
        const Uint8* state = SDL_GetKeyboardState(NULL);

        // clear screen
        SDL_SetRenderDrawColor(renderer_main, 255, 255, 255, 255);
        SDL_SetRenderDrawColor(renderer_treasure, 0, 0, 100, 255);
        SDL_RenderClear(renderer_main);
        SDL_RenderClear(renderer_treasure);
        
        // handle player collision
        if (player.mapType == MAP1) {
            drawMap(&map1, renderer_main);
            handlePlayerCollision(&player, &map1);
        }
        else if (player.mapType == MAP2) {
            drawMap(&map2, renderer_main);
            handlePlayerCollision(&player, &map2);
        }

        // draw player
        meleeAttackPlayer(&player, state, renderer_main);
        rangedAttackPlayer(&player, state, renderer_main);
        drawPlayer(&player, renderer_main);
        movePlayer(&player, state);

        openTreasurePlayer(&player, state, window_treasure);

        // present renderer
        SDL_RenderPresent(renderer_main);
        SDL_RenderPresent(renderer_treasure);
        SDL_Delay(1000/60);
    }
    
    // clean up
    SDL_DestroyRenderer(renderer_main);
    SDL_DestroyRenderer(renderer_treasure);
    SDL_DestroyWindow(window_main);
    SDL_DestroyWindow(window_treasure);
    SDL_Quit();

    return 0;
}