#include "geometry.hpp"
#include <array>
#include <cstdlib>
#include <math.h>

float pointdistance(array<float, 3> p1, array<float, 3> p2){
    return sqrt(pow(p1[0]-p2[0], 2)+pow(p1[1]-p2[1], 2)+pow(p1[2]-p2[2], 2));
}

array<float,3> normal(array<float, 3> p1, array<float, 3> p2){
    array<float,3> normal;
    normal[0] = p2[0]-p1[0];
    normal[1] = p2[1]-p1[1];
    normal[2] = p2[2]-p1[2];
    normal = normalize(normal);
    return normal;
}

float dotprod(array<float, 3> v1, array<float, 3> v2){
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

array<float,3> normalize(array<float,3> vec){
    float norm = vec[0]*vec[0];
    norm += vec[1]*vec[1];
    norm += vec[2]*vec[2];
    norm = sqrt(norm);
    vec[0] /= norm;
    vec[1] /= norm;
    vec[2] /= norm;
    return vec;
}

float randfloat(){
    return 2*(float(rand())/RAND_MAX)-1;
}
