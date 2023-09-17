#include "light.hpp"
#include "geometry.hpp"
#include <SDL2/SDL_pixels.h>
#include <array>

Light::Light(array<float, 3> direction){
    this->direction = normalize(direction);
}

SDL_Color colorx(SDL_Color objcolor, SDL_Color ambient_color){
    SDL_Color diff;
    diff.r = float(objcolor.r*ambient_color.r)/255;
    diff.g = float(objcolor.g*ambient_color.g)/255;
    diff.b = float(objcolor.b*ambient_color.b)/255;
    return diff;
}
SDL_Color coloradd(SDL_Color objcolor, SDL_Color ambient_color){
    SDL_Color add;
    add.r = min(objcolor.r+ambient_color.r, 255);
    add.g = min(objcolor.g+ambient_color.g, 255);
    add.b = min(objcolor.b+ambient_color.b, 255);
    return add;
}

SDL_Color color_scale(SDL_Color color, float scale){
    color.r = color.r*scale;
    color.g = color.g*scale;
    color.b = color.b*scale;
    return color;
}
