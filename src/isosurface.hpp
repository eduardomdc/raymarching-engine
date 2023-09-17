#ifndef ISOSURFACE
#define ISOSURFACE

#include <SDL2/SDL_stdinc.h>
#include <array>
#include <SDL2/SDL.h>

using namespace std;

class Isosurface {
public:
    virtual float distance(array<float, 3> pos);
    virtual void update(Uint32 dt);
    array<float, 3> center;
    SDL_Color color;
};

class Sphere : public Isosurface {
public:
    Sphere(float radius, array<float, 3> center);
    float distance(array<float, 3> pos);
    void update(Uint32 dt);
private:
    float radius;
    array<float, 3> speed;
};

class Plane : public Isosurface {
public:
    Plane(array<float, 3> center);
    float distance(array<float,3> pos);
};

class Sea : public Isosurface {
public:
    Sea(array<float, 3> center);
    float distance(array<float,3> pos);
    void update(Uint32 dt);
private:
    float phase;
};


#endif
