#include "light.hpp"
#include "geometry.hpp"
#include <array>

Light::Light(array<float, 3> direction){
    this->direction = normalize(direction);
}
