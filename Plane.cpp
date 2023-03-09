#include "Plane.h"
using namespace std;
#include <cmath>

//Constructor, sets the center of the plane and the normal vector
Plane::Plane(Tuple normalVector, Tuple c) {
    this->center = Tuple(c);
    this->planeNormalVector = Tuple(normalVector);
    this->planeNormalVector.normalize();
    this->planeNormalVector.w = 0;
    this->normal = this->planeNormalVector;
}

// return true if ray hits plane which will be the case if the ray was not parallel to the plane and set pass-by-reference argument t to be the distance from the origin to the intersection point.
// else, return false and set t to -1 to signify the ray missed the plane.
bool Plane::rayHitsPlane(const Tuple rayDirection, const Tuple rayOrigin, bool shadowCast) {
    double nDotV = this->planeNormalVector.dot(rayDirection);
    if (nDotV != 0) {
        Tuple temp = this->center;
        temp - rayOrigin;
        this->t = (temp.dot(this->planeNormalVector)) / nDotV;  
        if (!shadowCast) {
            this->currentObjPoint = (rayDirection * this->t) + rayOrigin;
        }
        return true; 
    }
    this->t = -1;
    return false;
}

//N DOT V == 0 means no intersection

/**

t = ( P –Ro ) DOT N
----------------------
N DOT V
Division by 0 will cause 
a run-time crash.
N DOT V is 0 when the 
ray is parallel to the 
plane so no 
intersection is possible.
If N DOT V is not zero, then we can take our value of t and plug-it into the points along ray equation...
A(t) = Ro + t * V

**/