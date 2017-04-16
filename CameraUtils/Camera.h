//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_CAMERA_H
#define CYLINDERS_CAMERA_H

#include "../Utils/Vector.h"
#include "Ray.h"

struct Camera {
    Vector eye, lookat, up, right;
    Number xMax, yMax;


    Camera( const Vector &eye_init, const Vector &lookat_init, const Vector &up_init, Number xMax_init, Number yMax_init );

    void setNewEyeAndLookat( const Vector &e, const Vector &l, const Vector &u );

    Ray getRay( Number xPos, Number yPos );
};

#endif //CYLINDERS_CAMERA_H
