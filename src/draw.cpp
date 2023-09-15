#include "draw.hpp"
#include "geometry.hpp"
#include "algebra.hpp"
#include "hyper.hpp"
#include "main.hpp"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

SDL_Point atScreen(pointnd p){
    SDL_Point point;
    point.x = int((p.vec[0]/(p.vec[2]+1.1))*HEIGHT/2+int(WIDTH/2));
    point.y = int(-(p.vec[1]/(p.vec[2]+1.1))*HEIGHT/2+int(HEIGHT/2));
    return point;
}

void drawLine(pointnd a, pointnd b, SDL_Renderer* renderer){
    SDL_Point pa = atScreen(a); 
    SDL_Point pb = atScreen(b);
    SDL_RenderDrawLine(renderer, pa.x, pa.y, pb.x, pb.y);
}

void drawObject(object obj, SDL_Renderer* renderer){
    short colors[3] = {255, 150, 150};
    for (int i=0; i<obj.edges.size(); i++){
        SDL_SetRenderDrawColor(renderer,colors[i%3],colors[(i+1)%3],colors[(i+2)%3],255);
        drawLine(obj.points[obj.edges[i].idxa], obj.points[obj.edges[i].idxb], renderer);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void drawBasis(std::vector<pointnd> basis, SDL_Renderer *renderer){
    std::vector<short> colors = {255,0,0};
    SDL_Point origin = atScreen({{0.7, -0.7},2});
    for(int i=0; i<basis.size(); i++){
        SDL_SetRenderDrawColor(renderer,colors[i%3],colors[(i+1)%3],colors[(i+2)%3],255);
        SDL_Point point = atScreen(scale(basis[i], 0.2));
        point.x -= atScreen({{0,0},2}).x;
        point.y -= atScreen({{0,0},2}).y;
        SDL_RenderDrawLine(renderer, origin.x, origin.y, point.x+origin.x, point.y+origin.y);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

SDL_Texture* writeText(const char* text, SDL_Color color){
    SDL_Surface* surf = TTF_RenderText_Blended_Wrapped(hyper->font, text, color, 200);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(hyper->renderer, surf);
    SDL_FreeSurface(surf);
    return tex;
}
