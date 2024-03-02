#include "state.h"

enum State menu(SDL_Renderer *renderer, const Uint8* keyboard_state, SDL_Texture** img_button) {
    // draw menu
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
    if (button(renderer, SDL_GetMouseState(NULL, NULL), (int[]){300, 100}, (int[]){WINDOW_WIDTH/2 - 300/2, 300}, img_button[0])) return GAME;
    if (button(renderer, SDL_GetMouseState(NULL, NULL), (int[]){300, 100}, (int[]){WINDOW_WIDTH/2 - 300/2, 420}, img_button[1])) return SETTINGS;
    if (button(renderer, SDL_GetMouseState(NULL, NULL), (int[]){300, 100}, (int[]){WINDOW_WIDTH/2 - 300/2, 540}, img_button[2])) return ABOUT;
    return MENU;
}

enum State settings(SDL_Renderer *renderer, const Uint8* keyboard_state, SDL_Texture** img_button) {
    // draw settings
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    SDL_RenderClear(renderer);
    if (button(renderer, SDL_GetMouseState(NULL, NULL), (int[]){50, 50}, (int[]){20, 20}, img_button[3])) return MENU;
    if (keyboard_state[SDL_SCANCODE_ESCAPE]) return MENU;
    return SETTINGS;
}

enum State about(SDL_Renderer *renderer, const Uint8* keyboard_state, SDL_Texture* img_about, SDL_Texture** img_button) {
    // draw about
    SDL_RenderCopy(renderer, img_about, NULL, NULL);
    if (button(renderer, SDL_GetMouseState(NULL, NULL), (int[]){50, 50}, (int[]){20, 20}, img_button[3])) return MENU;
    if (keyboard_state[SDL_SCANCODE_ESCAPE]) return MENU;
    return ABOUT;
}

enum State pause(SDL_Renderer *renderer, const Uint8* keyboard_state) {
    // draw pause
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    SDL_RenderClear(renderer);
    if (keyboard_state[SDL_SCANCODE_ESCAPE]) return GAME;
    return PAUSE;
}

enum State game_over(SDL_Renderer *renderer, const Uint8* keyboard_state, SDL_Texture* img_gameover) {
    // draw game over
    SDL_RenderCopy(renderer, img_gameover, NULL, NULL);
    if (keyboard_state[SDL_SCANCODE_RETURN]) return MENU;
    return GAMEOVER;
}