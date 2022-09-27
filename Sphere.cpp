#include "Sphere.h"
#include "Tuple.h"
using namespace std;
#include <cmath>


//Constructor, sets the center of the plane and the normal vector
Sphere::Sphere(double r, Tuple c) {
    this->radius = r;
    this->center = Tuple(c);
    this->center.turnToPoint();
    this->setColor(255,255,255);
}

// return true if ray hits plane which will be the case if the ray was not parallel to the plane and set pass-by-reference argument t to be the distance from the origin to the intersection point.
// else, return false and set t to -1 to signify the ray missed the plane.
bool Sphere::rayHitsSphere(const Tuple rayDirection, const Tuple rayOrigin) {
    Tuple v = Tuple(rayOrigin);
    v = v - this->center;
    double a = rayDirection.dot(rayDirection);
    double b = 2 * (v.dot(rayDirection));
    double c = (v.dot(v)) - (this->radius * this->radius);
    double discriminant = (b * b) - (4 * a * c);
    if (discriminant == 0) {  // one intersection point
        this->t = sqrt(discriminant);
        this->t += b * -1;
        this->t = this->t / (a*2);
        this->tRear = this->t;
        return true;
    }
    else if (discriminant > 0) { // two intersection points
        double solution1;
        double solution2;
        solution1 = sqrt(discriminant);
        solution2 = sqrt(discriminant);
        solution1 += b * -1;
        solution2 = (b * -1) - solution2;
        solution1 = solution1/(2*a);
        solution2 = solution2/(2*a);

        if (solution1 < solution2) {
            this->t = solution1;
            this->tRear = solution2;
        }
        else {
            this->t = solution2;
            this->tRear = solution1;
        }
        return true;
    }
    else { // no intersection points
        this->t = -1;
        this->tRear = -1;
        return false;
    }
    return false; // should never get here
}

//set the color
void Sphere::setColor(int r, int g, int b) {
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
}

//Let V = (O –C)
//Let a = D^2 = D dot D
//Let b = 2VD = 2 * (V dot D)
//Let c = V^2 –r^2 = (V dot V) - ^2