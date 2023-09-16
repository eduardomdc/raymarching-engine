#ifndef ISOSURFACE
#define ISOSURFACE

#include <array>

using namespace std;

class Isosurface {
public:
    virtual float distance(array<float, 3>);
    array<float, 3> center;
    array<float, 3> speed;
};

class Sphere : public Isosurface {
public:
    Sphere(float radius, array<float, 3>);
    float distance(array<float, 3>);
private:
    float radius;
};


#endif
