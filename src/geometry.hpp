#ifndef GEOMETRY
#define GEOMETRY

#include <array>

using namespace std;

float pointdistance(array<float,3> p1, array<float, 3> p2);
array<float,3> normal(array<float,3> p1, array<float, 3> p2);
array<float,3> normalize(array<float,3> vec);
float dotprod(array<float,3> v1, array<float,3> v2);
float randfloat();

#endif
