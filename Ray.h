#include <iostream> 
using namespace std;
#include "Tuple.h"
#ifndef RAY_HDR
#define RAY_HDR

class Ray {

public:

Tuple direction; // unit length direction vector
Tuple origin;     // starting point of the ray

};

#endif