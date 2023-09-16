#include "isosurface.hpp"
#include "geometry.hpp"
#include <array>
#include <iostream>
#include <cmath>

using namespace std;

float Isosurface::distance(array<float, 3>){return 0.0;}

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

float Sphere::distance(array<float, 3> pos){
    float distance = sqrt(squaredistance(pos, center));
    return distance - radius;
}
