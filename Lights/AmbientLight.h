#pragma once

#include "Light.h"

struct AmbientLight
    : public Light
{
    Color Lout;

  public:
    AmbientLight()
    {
        Lout = Color(1, 1, 1);
    }

    virtual ~AmbientLight(){};

    Color getIntensity(Vector &targetPoint)
    {
        return Lout;
    }

    Vector getDirection(Vector &targetPoint)
    {
        return Vector(0, 0, 0);
    }

    Number getDistance(Vector &targetPoint)
    {
        return Number(0);
    }
};
