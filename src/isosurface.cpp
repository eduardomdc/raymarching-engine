#include "isosurface.hpp"
#include "geometry.hpp"
#include <SDL2/SDL_stdinc.h>
#include <array>
#include <iostream>
#include <cmath>

using namespace std;

float Isosurface::distance(array<float, 3>){return 0.0;}
void Isosurface::update(Uint32 dt){}

Sphere::Sphere(float radius, array<float, 3> center) : Isosurface(){
    this->radius = radius;
    this->center = center;
    this->speed[0] = randfloat();
    this->speed[1] = randfloat();
    this->speed[2] = randfloat();
}

float squaredistance(array<float, 3> p1, array<float, 3> p2){
    return pow(p1[0]-p2[0], 2)+pow(p1[1]-p2[1], 2)+pow(p1[2]-p2[2], 2);
}

float squaredistancemod(array<float, 3> p1, array<float, 3> p2, float mod){
    return pow(fmod(p1[0],mod)-p2[0], 2)+pow(fmod(p1[1],mod)-p2[1], 2)+pow(fmod(p1[2],mod)-p2[2], 2);
}

float Sphere::distance(array<float, 3> pos){
    float distance = sqrt((squaredistance(pos, center)));
    return distance - radius;
}

Plane::Plane(array<float,3> center) : Isosurface(){
    this->center = center;
}

float Plane::distance(array<float,3> pos){
    return pos[1]-center[1];
}

Sea::Sea(array<float,3> center) : Isosurface(){
    this->center = center;
    phase = 0;
}

float Sea::distance(array<float,3> pos){
    return pos[1]-center[1]-sin(pos[0]+phase);
}

void Sea::update(Uint32 dt){
    phase += dt*0.001;
}

void Sphere::update(Uint32 dt){
    float bound = 2;
    center[0] += dt*0.001*speed[0]; 
    center[1] += dt*0.001*speed[1]; 
    center[2] += dt*0.001*speed[2]; 
    if (center[0] < -bound || center[0] > bound){
        speed[0] *= -1;
    }
    if (center[1] < -bound || center[1] > bound){
        speed[1] *= -1;
    }
    if (center[2] < -bound || center[2] > bound){
        speed[2] *= -1;
    }
}
