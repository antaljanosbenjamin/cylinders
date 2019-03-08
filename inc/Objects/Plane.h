#pragma once

#include "CameraUtils/Ray.h"
#include "Objects/Object.h"

class Plane : public Object {
  private:
    Vector normal;
    Number width, depth;
    Number widthPer2, depthPer2;

  public:
    Plane(Material *mat, Number width_init, Number depth_init);

    virtual ~Plane();

    Vector getNormalAtPoint(Vector &intersectPoint);

    ObjectPosition getPositionByUV(Number u, Number v);

    Number intersect(Ray &r, RayHit &hit);

  private:
    // It gets the point in the object's coordinate system
    bool planeContains(Vector v);
};
