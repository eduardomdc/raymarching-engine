#include "metaballs.hpp"
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

Metaballs::Metaballs(){
    running = true;
    window = nullptr;
    renderer = nullptr;
}

void Metaballs::initSDL(){
    cout<<"Starting SDL"<<endl;
    window = SDL_CreateWindow("Metaballsvision", 
            0,
            0, 
            WIDTH, 
            HEIGHT, 
            0);
    if (!window){
        cout<<"SDL window error"<<endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer){
        cout<<"SDL renderer error"<<endl;
        return;
    } 
}

void Metaballs::render(){
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderPresent(renderer);
}

void Metaballs::update(Uint32 dt){
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
            }
        }
    }
}
