// include libraries
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

// include files
#include "config.h"
#include "entity/player.h"
#include "entity/enemy.h"
#include "map.h"

// main function
int main() {
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        fprintf(stderr, "IMG_Init Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // create window
    SDL_Window* window_main = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window_main == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // create renderer
    SDL_Renderer* renderer_main = SDL_CreateRenderer(window_main, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer_main == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window_main);
        SDL_Quit();
        return 1;
    }

    // create player and map
    Player player = createPlayer(WINDOW_WIDTH/2, WINDOW_HEIGHT-140+1, 40, 60, 5);
    Enemy enemy1 = createEnemy(14, 6, 40, 60, 3, 14, 11);
    Enemy enemy2 = createEnemy(2, 5, 40, 60, 3, 7, 1);
    Enemy enemy3 = createEnemy(6, 5, 40, 60, 3, 7, 1);
    Enemy enemy4 = createEnemy(7, 3, 40, 60, 3, 12, 7);
    Enemy enemy5 = createEnemy(1, 2, 40, 60, 3, 4, 1);
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
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
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
        Uint32 time = SDL_GetTicks();
        const Uint8* state = SDL_GetKeyboardState(NULL);

        // clear screen
        SDL_SetRenderDrawColor(renderer_main, 255, 255, 255, 255);
        SDL_RenderClear(renderer_main);
        
        // handle player collision
        if (player.location == MAP1) {
            drawMap(&map1, renderer_main);
            handlePlayerCollision(&player, &map1);
            drawEnemy(&enemy1, renderer_main);
            moveEnemy(&enemy1, player.x, player.y);
            drawEnemy(&enemy2, renderer_main);
            moveEnemy(&enemy2, player.x, player.y);
            drawEnemy(&enemy3, renderer_main);
            moveEnemy(&enemy3, player.x, player.y);
            drawEnemy(&enemy4, renderer_main);
            moveEnemy(&enemy4, player.x, player.y);
            drawEnemy(&enemy5, renderer_main);
            moveEnemy(&enemy5, player.x, player.y);
        }
        else if (player.location == MAP2) {
            drawMap(&map2, renderer_main);
            handlePlayerCollision(&player, &map2);
        }

        // draw player
        attack1Player(&player, state, renderer_main, time);
        attack2Player(&player, state, renderer_main, time);
        drawPlayer(&player, renderer_main);
        movePlayer(&player, state);

        openChestPlayer(&player, state, renderer_main);

        // present renderer
        SDL_RenderPresent(renderer_main);
        SDL_Delay(1000/60);
    }
    
    // clean up
    SDL_DestroyRenderer(renderer_main);
    SDL_DestroyWindow(window_main);
    SDL_Quit();

    return 0;
}