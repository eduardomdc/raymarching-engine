#ifndef METABALLS
#define METABALLS
#define WIDTH 1280
#define HEIGHT 960
#define FPS 120

#include <SDL2/SDL.h>
#include <vector>

class Metaballs {
public:
    Metaballs();
    void initSDL();
    void render();
    void update(Uint32 dt);
    void input();
    void quit();
    bool running;
    SDL_Renderer* renderer;
    SDL_Window* window;
};

extern Metaballs* metaballs;

#endif
