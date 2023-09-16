#include "draw.hpp"
#include "metaballs.hpp"
#include <array>
#include <iostream>
#include <cmath>

void setpixel(unsigned int w, unsigned int h, SDL_Color color){
    Uint32 colorbits;
    colorbits = (color.r<<24) + (color.g<<16) + (color.b<<8) + color.a;
    metaballs->pixels[w+h*WIDTH] = colorbits;
}

Camera::Camera(){
    pos = {0,0,0};
    screen_distance = 1;
    screen_width = 1;
    screen_height = float(HEIGHT)/WIDTH;
}

array<float, 3> Camera::pixel_pos(array<unsigned int, 2> screen_pixel){
    // returns pixel position in 3d space relative to camera position.
    array<float, 3> pixel;
    pixel[2] = screen_distance;
    /* Screen pixels coordinates are the same as SDL's
     * (0,0) (1,0) (2,0)...
     * (0,1) (1,1)...
     * */
    pixel[0] = - screen_width/2 + (screen_pixel[0]+0.5)*screen_width/WIDTH;
    pixel[1] = - screen_height/2 + (screen_pixel[1]+0.5)*screen_height/HEIGHT;
    
    return pixel;
}

array<float, 3> Camera::direction(array<unsigned int, 2> pixel){
    array<float, 3> direction;
    // for now the camera is fixed to pointing towards the Z axis.
    direction = pixel_pos(pixel);
    // normalize vector
    float norm = direction[0]*direction[0];
    norm += direction[1]*direction[1];
    norm += direction[2]*direction[2];
    norm = sqrt(norm);
    direction[0] /= norm;
    direction[1] /= norm;
    direction[2] /= norm;
    return direction;
}

Raycaster::Raycaster() {
    object_color = {255, 0, 0, 255};
    max_iterations = 5;
    delta = 0.01; // min distance value required to count as ray collision
}

array<float,3> march(array<float,3> pos, array<float,3> dir, float distance){
    pos[0] += dir[0]*distance;
    pos[1] += dir[1]*distance;
    pos[2] += dir[2]*distance;
    return pos;
}

SDL_Color Raycaster::cast_ray(array<unsigned int, 2> pixel){
    /* ray march until it hits objects or exceeeds iterations max_iterations
     * returns color to be rendered to screen*/
//    std::cout<<"Casting ray "<<pixel[0]<<","<<pixel[1]<<std::endl;
    SDL_Color color = {0, 0, 0, 0};
    array<float,3> direction = metaballs->camera->direction(pixel);
    array<float,3> current_pos = metaballs->camera->pos; // start march at camera
    float distance = metaballs->distance(current_pos);
    unsigned int iterations = 0;
    while (iterations < max_iterations){
  //      std::cout << "distance is " << distance << std::endl;
   //     std::cout << "current_pos is " << current_pos[0] << ", "<<current_pos[1]<< ", " << current_pos[2] << std::endl;
        if (distance < delta){
            color = object_color;
            return color;
        }
        current_pos = march(current_pos, direction, distance);
        distance = metaballs->distance(current_pos);
        iterations++;
    }
    return color;
}
