using namespace std;
#ifndef PLANE_HDR
#define PLANE_HDR
#include "Shape.h"

class Plane: public Shape {

public:

Tuple center;
Tuple planeNormalVector;

//Constructor, sets the center of the plane and the normal vector
Plane(Tuple normalVector, Tuple c);

// return true if ray hits plane which will be the case if the ray was not parallel to the plane and set pass-by-reference argument t to be the distance from the origin to the intersection point.
// else, return false and set t to -1 to signify the ray missed the plane.
// edit: I am now storing t inside the objects themselves. 
bool rayHitsPlane(const Tuple rayDirection, const Tuple rayOrigin);

//set the color
void setColor(int r, int g, int b);

};

#endif