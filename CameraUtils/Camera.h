#pragma once

#include "../MathUtils/Vector.h"
#include "Ray.h"

struct Camera {
    Vector eye, lookat, up, right;
    Number xMax, yMax;


    Camera( const Vector &eye_init, const Vector &lookat_init, const Vector &up_init, Number xMax_init, Number yMax_init );

    void setNewEyeAndLookat( const Vector &e, const Vector &l, const Vector &u );

    Ray getRay( double xPos, double yPos );
};
