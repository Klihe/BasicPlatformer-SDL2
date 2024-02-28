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

    SDL_Surface* surface_player_idle = IMG_Load("src/img/player/player_idle.png");
    SDL_Texture* texture_player_idle = SDL_CreateTextureFromSurface(renderer_main, surface_player_idle);
    SDL_Surface* surface_enemy_left = IMG_Load("src/img/enemy/enemy_left.png");
    SDL_Texture* texture_enemy_left = SDL_CreateTextureFromSurface(renderer_main, surface_enemy_left);
    SDL_Surface* surface_enemy_right = IMG_Load("src/img/enemy/enemy_right.png");
    SDL_Texture* texture_enemy_right = SDL_CreateTextureFromSurface(renderer_main, surface_enemy_right);
    SDL_Surface* surface_block_ladder = IMG_Load("src/img/ladder.png");
    SDL_Texture* texture_block_ladder = SDL_CreateTextureFromSurface(renderer_main, surface_block_ladder);
    SDL_Surface* surface_block_solid = IMG_Load("src/img/cobble.png");
    SDL_Texture* texture_block_solid = SDL_CreateTextureFromSurface(renderer_main, surface_block_solid);
    SDL_Surface* surface_block_foward = IMG_Load("src/img/portal_foward.png");
    SDL_Texture* texture_block_foward = SDL_CreateTextureFromSurface(renderer_main, surface_block_foward);
    SDL_Surface* surface_block_backward = IMG_Load("src/img/portal_backward.png");
    SDL_Texture* texture_block_backward = SDL_CreateTextureFromSurface(renderer_main, surface_block_backward);
    SDL_Surface* surface_block_treasure = IMG_Load("src/img/treasure.png");
    SDL_Texture* texture_block_treasure = SDL_CreateTextureFromSurface(renderer_main, surface_block_treasure);

    // create player and map
    Player player = createPlayer(WINDOW_WIDTH/2, WINDOW_HEIGHT-160+1, 44, 64, 5);
    Enemy enemy[5] = {createEnemy(14, 6, 60, 80, 3, 14, 11),
                      createEnemy(2, 5, 60, 80, 3, 7, 1),
                      createEnemy(6, 5, 60, 80, 3, 7, 1),
                      createEnemy(7, 3, 60, 80, 3, 12, 7),
                      createEnemy(1, 2, 60, 80, 3, 4, 1)};
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
                {0,2,1,1,1,1,1,1,1,1,1,1,1,2,0,0},
                {0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,6},
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
        SDL_SetRenderDrawColor(renderer_main, 100, 100, 100, 255);
        SDL_RenderClear(renderer_main);
        
        // handle player collision
        if (player.location == MAP1) {
            drawMap(&map1, renderer_main, texture_block_ladder, texture_block_solid, texture_block_foward, texture_block_backward, texture_block_treasure);
            handlePlayerCollision(&player, &map1);
            for (int i = 0; i < 5; i++) {
                drawEnemy(&enemy[i], renderer_main, texture_enemy_left, texture_enemy_right);
                moveEnemy(&enemy[i], player.x, player.y);
            }
        }
        else if (player.location == MAP2) {
            drawMap(&map2, renderer_main, texture_block_ladder, texture_block_solid, texture_block_foward, texture_block_backward, texture_block_treasure);
            handlePlayerCollision(&player, &map2);
        }

        // draw player
        attack1Player(&player, state, renderer_main, time);
        attack2Player(&player, state, renderer_main, time);
        drawPlayer(&player, renderer_main, texture_player_idle);
        movePlayer(&player, state);

        openChestPlayer(&player, state, renderer_main);

        // present renderer
        SDL_RenderPresent(renderer_main);
        SDL_Delay(1000/60);
    }
    
    // clean up
    SDL_DestroyTexture(texture_player_idle);
    SDL_FreeSurface(surface_player_idle);
    SDL_DestroyRenderer(renderer_main);
    SDL_DestroyWindow(window_main);
    SDL_Quit();

    return 0;
}