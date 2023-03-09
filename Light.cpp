#include "Light.h"

Light::Light(Rgb intensity, Tuple point) {
    this->lightIntensity = intensity;
    this->lightPoint = point;
}