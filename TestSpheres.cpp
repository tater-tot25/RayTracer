#include "Tuple.h"
#include "easyppm.h"
#include "Ray.h"
#include "Plane.h"
#include "Shape.h"
#include "Sphere.h"
#include <cmath>
#define NUMOFPLANES 0 // increase with the number of planes added
#define NUMOFSHAPES 2 // increase with the number of shapes added
#define NUMOFSPHERES 2 // increase with the number of spheres added
using namespace std;


int main() {
  int bgc[3] = {0, 255, 0}; // green
  //Plane plane1(Tuple(0,0,-1), Tuple(0,0,10));
  //Plane plane2(Tuple(0,1,-1), Tuple(0,0,10));
  //plane1.setColor(0, 0, 255); // blue
  //plane2.setColor(255, 0, 0); // red
  Sphere sphere1(2.5, Tuple(0,0,10));
  Sphere sphere2(1, Tuple(0,0,6));
  sphere1.setColor(255, 128, 0); // orange
  sphere2.setColor(0, 255, 0); // green
  double imagePixelSize = 200;
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
  //Plane planes[NUMOFPLANES] = {plane1, plane2}; // add all planes to this array
  Sphere spheres[NUMOFSPHERES] = {sphere1, sphere2}; // add all spheres to this array
  for (double t = 0; t <= h; t += h/imagePixelSize) {
    for (double s = 0; s <= w; s += w/imagePixelSize) {

      Shape shapes[NUMOFSHAPES];
      Tuple P = Start + (s*X) + (t*Y);
      R.direction = P - R.origin;
      R.direction.normalize();

      //check for intersections with every shape before checking the boolean, this is not efficient, but I'm not sure how to check every object with one raycast

      int countShapes = 0;

      /**
      for (int i = 0; i < NUMOFPLANES; i ++) {
        bool temp = planes[i].rayHitsPlane(R.direction, R.origin);
        if (temp) {
          shapes[countShapes] = planes[i]; // add the plane to the list of all shapes
          countShapes ++; // increment the number of shapes for sorting later
        }
      }
      **/

      
      for (int i = 0; i < NUMOFSPHERES; i++) {
        bool temp = spheres[i].rayHitsSphere(R.direction, R.origin);   // For use if both object types are in the scene
        if (temp) {
          shapes[countShapes] = spheres[i]; // add the sphere to the list of all shapes
          countShapes ++; // increment the number of shapes for sorting later
        }
      }


      
      if (countShapes > 0) { // there was an intersection
        bool running = true;
        while (running && countShapes > 1) {
          cout << shapes[0].t << endl;
          cout << shapes[1].t << endl;
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
        easyppm_set(&myImage, trackX, trackY, easyppm_rgb(shapes[0].color[0], shapes[0].color[1], shapes[0].color[2]));
      }
      else { // no intersection
        easyppm_set(&myImage, trackX, trackY, easyppm_rgb(bgc[0], bgc[1], bgc[2])); // miss plane
      }


      trackX++;
    }
    trackY--;
    trackX = 0;
  }
  easyppm_write(&myImage, "test_spheres.ppm");
  return 0;
}

//Use the sphere from the pictured test case below...

//a) Try creating just a single ray from the origin point (0,0,0, 1) with direction vector of (0, 0, 1). You should find two intersection points (0,0,7.5) where t is 7.5 and (0,0,12.5), where t is 12.5.

//b) Try testing a single ray from origin of (0,2.6,0) and direction (0, 0, 1). This ray should pass just above the sphere and miss.