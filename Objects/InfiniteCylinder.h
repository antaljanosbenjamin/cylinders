//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_INFINITCYLINDER_H
#define CYLINDERS_INFINITCYLINDER_H

#include "Object.h"
#include "../CameraUtils/Ray.h"

class InfiniteCylinder
        : public Object {
    Number radius;

public:
    InfiniteCylinder( Material *material_init, Number radius_init );

    virtual ~InfiniteCylinder();

    // Világ koordinátákban lévő vektort kap
    Vector getNormalAtPoint( Vector &intersectPoint );

    Number intersect( Ray &r, RayHit &hit );
};

#endif //CYLINDERS_INFINITCYLINDER_H
