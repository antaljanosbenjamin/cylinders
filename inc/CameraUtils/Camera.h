#pragma once

#include "CameraUtils/Ray.h"
#include "MathUtils/Vector.h"

struct Camera {
    Vector eye;
    Vector lookat;
    Vector up;
    Vector right;
    Number xMax;
    Number yMax;

    Camera(const Vector &eye_init, const Vector &lookat_init, const Vector &up_init,
           Number xMax_init, Number yMax_init);

    void setNewEyeAndLookat(const Vector &e, const Vector &l, const Vector &u);

    Ray getRay(double xPos, double yPos);
};
