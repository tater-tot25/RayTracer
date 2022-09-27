#include <iostream> 
using namespace std;
#include "Tuple.h"
#include "Shape.h"
#ifndef SPHERE_HDR
#define SPHERE_HDR

class Sphere: public Shape {

public:

Tuple center;
double radius;
double tRear;

//Constructor, sets the center of the sphere and the radius
Sphere(double r, Tuple c);

bool rayHitsSphere(const Tuple rayDirection, const Tuple rayOrigin);

//set the color
void setColor(int r, int g, int b);

};

#endif