#ifndef ISOSURFACE
#define ISOSURFACE

#include <array>

using namespace std;

class Isosurface {
public:
    virtual float distance(array<float, 3>);
};

class Sphere : public Isosurface {
public:
    Sphere(float radius, array<float, 3>);
    float distance(array<float, 3>);
private:
    array<float, 3> center;
    float radius;
};


#endif
