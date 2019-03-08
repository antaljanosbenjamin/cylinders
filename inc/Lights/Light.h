#pragma once

#include "Materials/Color.h"
#include "MathUtils/Vector.h"

struct Light {
    virtual Color getIntensity(Vector &targetPoint) = 0;

    virtual Vector getDirection(Vector &targetPoint) = 0;

    virtual Number getDistance(Vector &targetPoint) = 0;

    virtual ~Light(){};
};
