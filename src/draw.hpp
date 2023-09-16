#ifndef DRAW
#define DRAW

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <array>
#include <SDL2/SDL.h>

using namespace std;

void setpixel(unsigned int w, unsigned int h, SDL_Color color);

class Camera {
public:
    Camera();
    array<float,3> pos;
    float screen_distance; // distance between ray casting origin and pixel plane
    float screen_width; // screen_width is always 1
    float screen_height; // screen_height is scaled according to resolution ratio
    array<float, 3> direction(array<unsigned int,2> pixel); // get raycast direction vector for pixel (x,y)
    array<float, 3> pixel_pos(array<unsigned int, 2> pixel); // get 3d position of pixel in screen plane
};

class Raycaster {
public:
    Raycaster();
    SDL_Color cast_ray(array<unsigned int, 2> pixel);
    SDL_Color object_color;
    float delta;
    unsigned int max_iterations;
};

#endif
