#pragma once

#include "CameraUtils/Ray.h"
#include "Objects/Object.h"

class InfiniteCylinder : public Object {
    Number radius;

  public:
    InfiniteCylinder(Material *material_init, Number radius_init);

    virtual ~InfiniteCylinder();

    /*
     * @intersectPoint: a surface point in the world's coordinate system
     * returns: the normal vector at the specified surface point
     */
    Vector getNormalAtPoint(Vector &intersectPoint);

    Number intersect(Ray &r, RayHit &hit);
};
