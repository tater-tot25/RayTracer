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


//Given a ray's direction and its origin, determine whether there was a collision,
//and store it's magnitude to the shape's t value
bool rayHitsSphere(const Tuple rayDirection, const Tuple rayOrigin, bool shadowCast);

//given an intersect point, create a normal vector for the sphere
void setNormal(Tuple intersectPoint);

};

#endif