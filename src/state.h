#ifndef STATE_H
#define STATE_H

#include <SDL.h>

enum State {
    MENU,
    GAME,
    PAUSE,
    GAMEOVER,
};

enum State menu(SDL_Renderer *renderer, const Uint8* keyboard_state);
enum State pause(SDL_Renderer *renderer, const Uint8* keyboard_state);
enum State game_over(SDL_Renderer *renderer, const Uint8* keyboard_state);

#endif // STATE_H