#ifndef STATE_H
#define STATE_H

#include <SDL.h>

#include "config.h"
#include "UI/ui.h"

enum State {
    MENU,
    SETTINGS,
    ABOUT,
    GAME,
    PAUSE,
    GAMEOVER,
};

enum State menu(SDL_Renderer *renderer, const Uint8* keyboard_state, SDL_Texture** img_button);
enum State settings(SDL_Renderer *renderer, const Uint8* keyboard_state, SDL_Texture** img_button);
enum State about(SDL_Renderer *renderer, const Uint8* keyboard_state, SDL_Texture* img_about, SDL_Texture** img_button);
enum State pause(SDL_Renderer *renderer, const Uint8* keyboard_state);
enum State game_over(SDL_Renderer *renderer, const Uint8* keyboard_state, SDL_Texture* img_gameover);

#endif // STATE_H