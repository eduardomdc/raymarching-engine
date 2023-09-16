#ifndef METABALLS
#define METABALLS
#define WIDTH 500
#define HEIGHT 500
#define FPS 30

#include "isosurface.hpp"
#include "draw.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <array>

using namespace std;

class Metaballs {
public:
    Metaballs();
    void initSDL();
    void render();
    void update(Uint32 dt);
    void input();
    void quit();
    float distance(array<float, 3> pos);
    bool running;
    SDL_Texture* texture;
    Uint32* pixels;
    SDL_Renderer* renderer;
    SDL_Window* window;
    vector<Isosurface*> objects;
    Camera* camera;
    Raycaster* raycaster;
};

extern Metaballs* metaballs;

#endif
