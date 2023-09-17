#include "draw.hpp"
#include "metaballs.hpp"
#include "geometry.hpp"
#include "light.hpp"
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
    pixel[1] = + screen_height/2 - (screen_pixel[1]+0.5)*screen_height/HEIGHT;
    
    return pixel;
}

array<float, 3> Camera::direction(array<unsigned int, 2> pixel){
    array<float, 3> direction;
    // for now the camera is fixed to pointing towards the Z axis.
    direction = pixel_pos(pixel);
    // normalize vector
    return normalize(direction);
}

Raycaster::Raycaster() {
    object_color = {255, 50, 50, 255};
    max_iterations = 30;
    delta = 0.03; // min distance value required to count as ray collision
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
    SDL_Color color = metaballs->ambient_color;
    array<float,3> direction = metaballs->camera->direction(pixel);
    array<float,3> current_pos = metaballs->camera->pos; // start march at camera
    array<float,3> last_pos;
    float distance = metaballs->distance(current_pos);
    for(int iterations=0; iterations<max_iterations; iterations++){
  //      std::cout << "distance is " << distance << std::endl;
   //     std::cout << "current_pos is " << current_pos[0] << ", "<<current_pos[1]<< ", " << current_pos[2] << std::endl;
        if (distance < delta){
            // calculate normal and light dotprod
            array<float,3> normal;
            float epsilon = 0.01;
            array<float,3> sample_pos = current_pos;
            sample_pos[0] += epsilon;
            float xnorm = metaballs->distance(sample_pos);
            sample_pos = current_pos;
            sample_pos[1] += epsilon;
            float ynorm = metaballs->distance(sample_pos);
            sample_pos = current_pos;
            sample_pos[2] += epsilon;
            float znorm = metaballs->distance(sample_pos);
            normal[0] = (xnorm-distance)/epsilon;
            normal[1] = (ynorm-distance)/epsilon;
            normal[2] = (znorm-distance)/epsilon;
            float lightlevel = max(float(0),dotprod(normal, metaballs->light->direction));
            SDL_Color direct_light = color_scale({255,255,255}, lightlevel);
            SDL_Color final = coloradd(colorx(object_color, metaballs->ambient_color), colorx(object_color, direct_light));
            float occlusionlevel = 1-float(iterations)/max_iterations;
            final = color_scale(final, occlusionlevel);
            return final;
        }
        last_pos = current_pos;
        current_pos = march(current_pos, direction, distance);
        distance = metaballs->distance(current_pos);
    }
    return color;
}
