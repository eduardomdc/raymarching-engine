#ifndef DRAW
#define DRAW

#include "geometry.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <vector>

SDL_Point screenPoint(pointnd p);
void drawLine(pointnd a, pointnd b, SDL_Renderer* renderer);
void drawObject(object obj, SDL_Renderer* renderer);
void drawBasis(std::vector<pointnd> basis, SDL_Renderer* renderer);
SDL_Texture* writeText(const char* text, SDL_Color color);

#endif
