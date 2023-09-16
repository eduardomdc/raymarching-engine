#ifndef LIGHT
#define LIGHT

#include <array>

using namespace std;

class Light {
public:
    Light(array<float,3> direction);
    array<float,3> pos;
    array<float,3> direction;
};

#endif
