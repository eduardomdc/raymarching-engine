#include "isosurface.hpp"
#include "geometry.hpp"
#include <array>
#include <iostream>

float Isosurface::distance(array<float, 3>){return 0.0;}

Sphere::Sphere(float radius, array<float, 3> center) : Isosurface(){
    this->radius = radius;
    this->center = center;
}

float Sphere::distance(array<float, 3> pos){
    float distance = pointdistance(center, pos);
    return distance - radius;
}
