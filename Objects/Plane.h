//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_PLANE_H
#define CYLINDERS_PLANE_H

#include "Object.h"
#include "../CameraUtils/Ray.h"

class Plane
        : public Object {
    Vector normal;
    Number width, depth;
    Number widthPer2, depthPer2;

public:
    Plane( Material &mat, Number width_init, Number depth_init );

    virtual ~Plane();

    Vector getNormalAtPoint( Vector &intersectPoint );

    ObjectPosition getPositionByUV( Number u, Number v );

    // Object koordinátákban kapja meg
    bool planeContains( Vector v );

    Number intersect( Ray &r, RayHit &hit );
};


#endif //CYLINDERS_PLANE_H
