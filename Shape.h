#include <iostream> 
#include "Rgb.h"
using namespace std;
#include "Tuple.h"
#include "Ray.h"
#include "Light.h"
#ifndef SHAPE_HDR
#define SHAPE_HDR

class Shape {

public:

double t;
Rgb materialReflectance;
int exponent; 
Tuple normal;
Tuple currentObjPoint;
string id;

Rgb lightAmbient( const Rgb& materialReflectance, const Rgb& lightIntensity );

Rgb lightDiffuse(const Rgb& materialReflectance, const Tuple& objectPoint, const Tuple& objectNormal, const Rgb& lightIntensity, const Tuple& lightPoint);

Rgb lightSpecular(const Rgb& materialReflectance, const Tuple& objectPoint, const Tuple& objectNormal, 
                  const Rgb& lightIntensity, const Tuple& lightPoint,
									const Tuple& eyePoint, int exponent);

void setValues(double r, double g, double b, int exp);

void setID(string name);


//calculate the total light for one lightsource
Rgb getTotalLight(Light light, Tuple camera);


    
};

#endif