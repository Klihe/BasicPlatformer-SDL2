#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>

SDL_Texture* loadTexture(const char* file_path, SDL_Renderer* renderer);

#endif // TEXTURE_H