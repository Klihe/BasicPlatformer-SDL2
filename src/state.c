#include "state.h"

enum State menu(SDL_Renderer *renderer, const Uint8* keyboard_state) {
    // draw menu
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_RenderClear(renderer);
    if (button(renderer, SDL_GetMouseState(NULL, NULL), (int[]){100, 50}, (int[]){100, 100})) return GAME;
    return MENU;
}

enum State pause(SDL_Renderer *renderer, const Uint8* keyboard_state) {
    // draw pause
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    SDL_RenderClear(renderer);
    if (keyboard_state[SDL_SCANCODE_ESCAPE]) return GAME;
    return PAUSE;
}

enum State game_over(SDL_Renderer *renderer, const Uint8* keyboard_state) {
    // draw game over
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    SDL_RenderClear(renderer);
    if (keyboard_state[SDL_SCANCODE_RETURN]) return MENU;
    return GAMEOVER;
}