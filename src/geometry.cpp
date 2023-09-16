#include "geometry.hpp"
#include <math.h>

float pointdistance(array<float, 3> p1, array<float, 3> p2){
    return sqrt(pow(p1[0]-p2[0], 2)+pow(p1[1]-p2[1], 2)+pow(p1[2]-p2[2], 2));
}
