// include libraries
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

// include files
#include "config.h"
#include "texture.h"
#include "entity/player.h"
#include "entity/enemy.h"
#include "map.h"
#include "UI/ui.h"
#include "state.h"

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

    SDL_Texture* img_background = loadTexture("src/img/background.png", renderer_main);
    SDL_Texture* img_gameover = loadTexture("src/img/gameover.png", renderer_main);
    SDL_Texture* img_block_ladder = loadTexture("src/img/ladder.png", renderer_main);
    SDL_Texture* img_block_solid = loadTexture("src/img/cobble.png", renderer_main);
    SDL_Texture* img_block_foward = loadTexture("src/img/portal_foward.png", renderer_main);
    SDL_Texture* img_block_backward = loadTexture("src/img/portal_backward.png", renderer_main);
    SDL_Texture* img_block_treasure = loadTexture("src/img/treasure.png", renderer_main);
    SDL_Texture* img_block_lava = loadTexture("src/img/lava.png", renderer_main);

    SDL_Texture* img_player[4] = {loadTexture("src/img/player/player_1.png", renderer_main),
                                  loadTexture("src/img/player/player_2.png", renderer_main),
                                  loadTexture("src/img/player/player_3.png", renderer_main),
                                  loadTexture("src/img/player/player_4.png", renderer_main)};

    SDL_Texture* img_enemy[4] = {loadTexture("src/img/enemy/enemy_1.png", renderer_main),
                                 loadTexture("src/img/enemy/enemy_2.png", renderer_main),
                                 loadTexture("src/img/enemy/enemy_3.png", renderer_main),
                                 loadTexture("src/img/enemy/enemy_4.png", renderer_main)};                             

    enum State game_state = MENU;
    // create player and map
    Player player = createPlayer(WINDOW_WIDTH/2, WINDOW_HEIGHT-160+1, 44, 64, 5);
    Enemy enemy[5] = {createEnemy(14, 6, 56, 64, 3, 14, 11),
                      createEnemy(2, 5, 56, 64, 3, 3, 1),
                      createEnemy(6, 5, 56, 64, 3, 7, 5),
                      createEnemy(7, 3, 56, 64, 3, 12, 7),
                      createEnemy(1, 2, 56, 64, 3, 4, 1)};
    Map map1 = {{{0,0,0,0,0,0,0,0,0,3,0,0,0,5,0,0},
                {0,4,0,3,0,0,0,0,0,2,1,1,1,1,1,0},
                {0,1,1,2,1,0,0,3,0,2,0,3,0,0,0,0},
                {0,0,0,2,0,0,0,2,1,1,1,2,1,0,0,0},
                {0,3,0,2,0,0,0,2,0,0,0,2,0,0,0,0},
                {0,2,1,1,7,1,1,1,0,0,0,2,0,3,0,0},
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
        //Uint32 mouse_state = SDL_GetMouseState(NULL, NULL);
        const Uint8* state = SDL_GetKeyboardState(NULL);

        // clear screen
        SDL_RenderCopy(renderer_main, img_background, NULL, NULL);
        
        switch (game_state) {
            case MENU:
                game_state = menu(renderer_main, state);
                break;
            case SETTINGS:
                game_state = settings(renderer_main, state);
                break;
            case ABOUT:
                game_state = about(renderer_main, state);
                break;
            case GAME:
                if (state[SDL_SCANCODE_ESCAPE]) game_state = PAUSE;
                if (player.health <= 0) game_state = GAMEOVER;
                switch (player.location) {
                    case MAP1:
                        drawMap(&map1, renderer_main, img_block_ladder, img_block_solid, img_block_foward, img_block_backward, img_block_treasure, img_block_lava);
                        handlePlayerCollision(&player, &map1);
                        for (int i = 0; i < 5; i++) {
                            drawEnemy(&enemy[i], renderer_main, img_enemy, time);
                            moveEnemy(&enemy[i], player.x, player.y);
                            enemy[i].health -= attackCollision(&player.attack1Rect, &enemy[i].rect, player.attack1Active, player.attack1Damage);
                            enemy[i].health -= attackCollision(&player.attack2Rect_left, &enemy[i].rect, player.attack2Active, player.attack2Damage);
                            enemy[i].health -= attackCollision(&player.attack2Rect_right, &enemy[i].rect, player.attack2Active, player.attack2Damage);
                            updateEnemy(&enemy[i]);
                            player.health -= attackCollision(&enemy[i].attackRect, &player.rect, enemy[i].attackActive, enemy[i].attackDamage);
                        }
                        break;
                    case MAP2:
                        drawMap(&map2, renderer_main, img_block_ladder, img_block_solid, img_block_foward, img_block_backward, img_block_treasure, img_block_lava);
                        handlePlayerCollision(&player, &map2);
                        break;
                }
                // draw player
                attack1Player(&player, state, renderer_main, time);
                attack2Player(&player, state, renderer_main, time);
                drawPlayer(&player, renderer_main, img_player, time);
                movePlayer(&player, state);
                updatePlayer(&player);
                healthBar(renderer_main, player.health);

                chestPlayer(&player, state, renderer_main, time);
                inventoryPlayer(&player, state, renderer_main, time);
                break;
            case PAUSE:
                game_state = pause(renderer_main, state);
                break;
            case GAMEOVER:
                game_state = game_over(renderer_main, state);
                break;
        }
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