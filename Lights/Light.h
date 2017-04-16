//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_LIGHT_H
#define CYLINDERS_LIGHT_H


#include "../Materials/Color.h"
#include "../MathUtils/Vector.h"

struct Light {
    virtual Color getIntensity( Vector &targetPoint ) = 0;

    virtual Vector getDirection( Vector &targetPoint ) = 0;

    virtual Number getDistance( Vector &targetPoint ) = 0;

    virtual Light *clone() = 0;

    virtual ~Light() {};
};


#endif //CYLINDERS_LIGHT_H
