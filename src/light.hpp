#ifndef LIGHT
#define LIGHT

#include <array>
#include <SDL2/SDL.h>

using namespace std;

SDL_Color color_scale(SDL_Color color, float scale);
SDL_Color colorx(SDL_Color objcolor, SDL_Color ambient_color);
SDL_Color coloradd(SDL_Color objcolor, SDL_Color ambient_color);

class Light {
public:
    Light(array<float,3> direction);
    array<float,3> pos;
    array<float,3> direction;
    SDL_Color color;
};

#endif
