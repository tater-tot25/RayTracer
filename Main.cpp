#include "Tuple.h"
#include "easyppm.h"
#include "Ray.h"
#include "Plane.h"
#include "Shape.h"
#include "Sphere.h"
#include <cmath>
#define NUMOFPLANES 1 // increase with the number of planes added
#define NUMOFSPHERES 4 // increase with the number of spheres added
#define NUMOFSHAPES 4 // increase with the number of shapes added
#define NUMOFLIGHTS 2 // increase with the number of lights added
using namespace std;


int main() {
  int bgc[3] = {0, 255, 0}; // green

  Plane plane1(Tuple(1,0,-1), Tuple(0,0,11));
  Sphere sphere1(2.5, Tuple(4,0,7));
  Sphere sphere2(1, Tuple(1,0,8));
  Sphere sphere3(2, Tuple(-2,2,10));
  Sphere sphere4(1, Tuple(-1,-1,4));
  Rgb intensity(0.3, 0.3, 0.3); //dim white light
  Tuple lightPoint(3, 6, -1, 1);
  Light light1(intensity, lightPoint);
  Rgb intensity2(0.1, 0.1, 0.12); //blueish light
  Tuple lightPoint2(-2, 4, -1, 1);
  Light light2(intensity2, lightPoint2);
  plane1.setValues(0.5, 0.5, 0.5, 7); // gray/white plane
  sphere1.setValues(0.5, 0.1, 0.5, 5); // purple sphere
  sphere2.setValues(0.3, 0.2, 0.5, 7); // pink sphere
  sphere3.setValues(0.2,0.6,0.2, 3); //green sphere
  sphere4.setValues(0.1,0.1,0.6, 1); //blue sphere
  plane1.setID("plane1");  // id is for future shadow implementation
  sphere1.setID("sphere1");
  sphere2.setID("sphere2");
  sphere3.setID("sphere3");
  sphere4.setID("sphere4");

  double imagePixelSize = 1700;
  double h = 4;
  double w = 4;
  double front_clip = 4;
  PPM myImage = easyppm_create(imagePixelSize, imagePixelSize, IMAGETYPE_PPM);
  Tuple X (1,0,0,0);
  Tuple Y (0,1,0,0);
  Tuple Z (0,0,1,0);
  Tuple Start(-w/2, -h/2, front_clip, 1);
  Ray R;
  R.origin.turnToPoint();
  int trackX = 0;
  int trackY = imagePixelSize-1;
  Plane planes[NUMOFPLANES] = {plane1}; // add all planes to this array
  Sphere spheres[NUMOFSPHERES] = {sphere1, sphere2, sphere3, sphere4}; // add all spheres to this array
  Light lights[NUMOFLIGHTS] = {light1, light2}; // add all lights to this array
  for (double t = 0; t <= h; t += h/imagePixelSize) {
    for (double s = 0; s <= w; s += w/imagePixelSize) {

      Shape shapes[NUMOFSHAPES];
      Tuple P = Start + (s*X) + (t*Y);
      R.direction = P - R.origin;
      R.direction.normalize();

      //check for intersections with every shape before checking the boolean, this is not efficient, but I'm not sure how to check every object with one raycast

      int countShapes = 0;

      
      for (int i = 0; i < NUMOFPLANES; i ++) {
        bool temp = planes[i].rayHitsPlane(R.direction, R.origin, false);
        if (temp) {
          shapes[countShapes] = planes[i]; // add the plane to the list of all shapes
          countShapes ++; // increment the number of shapes for sorting later
        }
      }
      

      
      for (int i = 0; i < NUMOFSPHERES; i++) {
        bool temp = spheres[i].rayHitsSphere(R.direction, R.origin, false);   // For use if both object types are in the scene
        if (temp) {
          shapes[countShapes] = spheres[i]; // add the sphere to the list of all shapes
          countShapes ++; // increment the number of shapes for sorting later
        }
      }
      

      
      if (countShapes > 0) { // there was an intersection
        bool running = true;
        while (running && countShapes > 1) {
          bool madeSwap = false;
          for (int i = 0; i < countShapes - 1; i ++) {
            if (shapes[i+1].t < shapes[i].t) {
              Shape temp = shapes[i];
              shapes[i] = shapes[i+1];
              shapes[i+1] = temp;
              madeSwap = true;
            }
          }
          if (!madeSwap) {
            running = false;
          }
        }
        // pick the first object
        Rgb shader;
        Tuple origin;
        origin.turnToPoint();
        for (int i = 0; i < NUMOFLIGHTS; i++) {
          shader = shader + shapes[0].getTotalLight(lights[0], origin);
        }
        easyppm_set(&myImage, trackX, trackY, easyppm_rgb(shader.getR() * 255, shader.getG() * 255, shader.getB() * 255));
      }
      else { // no intersection
        easyppm_set(&myImage, trackX, trackY, easyppm_rgb(bgc[0], bgc[1], bgc[2])); // miss plane
      }


      trackX++;
    }
    trackY--;
    trackX = 0;
  }
  easyppm_write(&myImage, "test_trace.ppm");
  return 0;
}