#ifndef METABALLS
#define METABALLS
#define WIDTH 200
#define HEIGHT 200
#define FPS 15

#include "isosurface.hpp"
#include "draw.hpp"
#include "light.hpp"
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
    void spawnballs(int amount);
    bool running;
    SDL_Texture* texture;
    Uint32* pixels;
    SDL_Renderer* renderer;
    SDL_Window* window;
    vector<Isosurface*> objects;
    Camera* camera;
    Raycaster* raycaster;
    Light* light;
    SDL_Color ambient_color;
};

extern Metaballs* metaballs;

#endif
