#include <iostream> 
#include "Rgb.h"
using namespace std;
#include "Tuple.h"
#include "Ray.h"
#ifndef LIGHT_HDR
#define LIGHT_HDR

class Light {

public:

Rgb lightIntensity;
Tuple lightPoint;

Light(Rgb intensity, Tuple point);
    
};

#endif