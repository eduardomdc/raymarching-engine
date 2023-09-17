#include "metaballs.hpp"
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <random>

Metaballs* metaballs;

int main(){
    srand(time(NULL));
    std::cout<<"Initializing..."<<std::endl;
    metaballs = new Metaballs();
    metaballs->initSDL();
    Uint32 time = SDL_GetTicks();
    Uint32 delta;
    Uint32 spf = 1000/FPS;
    while(metaballs->running){
        metaballs->render();
        metaballs->update(spf);
        metaballs->input();
        delta = SDL_GetTicks()-time;
        if (delta < spf){
            //std::cout<<spf-delta<<std::endl;
            SDL_Delay(spf-delta);
        }
        time = SDL_GetTicks();
    }
    std::cout<<"Exiting..."<<std::endl;
    return 0;
}
