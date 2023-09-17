#include "metaballs.hpp"
#include "geometry.hpp"
#include "isosurface.hpp"
#include "draw.hpp"
#include "light.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <array>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

Metaballs::Metaballs(){
    running = true;
    window = nullptr;
    renderer = nullptr;
    objects = {};
    pixels = new Uint32[WIDTH*HEIGHT];
    camera = new Camera();
    raycaster = new Raycaster();
    light = new Light({1.0, 1.0, -1.0});
    //objects.push_back(new Sea({0, -5, 0}));
    ambient_color = {135/2, 206/2, 235/2};
    spawnballs(10);
}

void Metaballs::spawnballs(int amount){
    for (int i=0; i<amount;i++){
        Sphere* ball = new Sphere(1, {randfloat(), randfloat(), 8+randfloat()});
        objects.push_back(ball);
    } 
}

void Metaballs::initSDL(){
    cout<<"Starting SDL"<<endl;
    window = SDL_CreateWindow("Metaballs!", 
            0,
            0, 
            WIDTH, 
            HEIGHT, 
            0);
    if (!window){
        cout<<"SDL window error"<<endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);//SDL_RENDERER_PRESENTVSYNC);
    if (!renderer){
        cout<<"SDL renderer error"<<endl;
        return;
    } 
    SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
    if (!texture){
        cout<<"SDL texture error"<<endl;
        return;
    }
}

void Metaballs::render(){

    #pragma omp parallel for
    for (uint i=0; i<WIDTH; i++){
        for (uint j=0; j<HEIGHT; j++){
            setpixel(i, j, raycaster->cast_ray({i,j}));
        }
    }

    SDL_UpdateTexture(texture, NULL, pixels, WIDTH*sizeof(Uint32));
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void Metaballs::update(Uint32 dt){
    float bound = 2;
    for (int i=0; i<objects.size(); i++){
        objects[i]->update(dt); 
    }
}


void Metaballs::quit(){
    cout<<"Closing systems..."<<endl;
    running = false;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout<<"SDL killed"<<endl;
}

void Metaballs::input(){
    SDL_Event current;
    while(SDL_PollEvent(&current)){
        switch (current.type) {
        case SDL_QUIT:
            quit();
            break;
        case SDL_KEYDOWN:
            switch (current.key.keysym.sym){
                case SDLK_w:
                    camera->pos[2] += 0.3;
                    break;
                case SDLK_s:
                    camera->pos[2] -= 0.3;
                    break;
                case SDLK_a:
                    camera->pos[0] -= 0.3;
                    break;
                case SDLK_d:
                    camera->pos[0] += 0.3;
                    break;
            }
        }
    }
}

float Metaballs::distance(array<float, 3> pos){
    // returns distance function value at pos
    float dis;//MAXFLOAT;
    // for now there will be no smoothness
    /*pos[0] = fmod(pos[0], 15);
    pos[1] = fmod(pos[1], 15);
    pos[2] = fmod(pos[2], 15);*/
    float alpha = 0.15;
    float sum = 0;
    for (int i=0; i<objects.size(); i++){
        float this_dis = objects[i]->distance(pos); 
        //if (this_dis < dis) dis = this_dis;
        sum += exp(-this_dis/alpha);
    }
    sum /= objects.size();
    sum = log(sum);
    sum *= -alpha;
    dis = sum;

    return dis; 
}
