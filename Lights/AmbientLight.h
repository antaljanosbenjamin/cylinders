//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_AMBIENTLIGHT_H
#define CYLINDERS_AMBIENTLIGHT_H


#include "Light.h"

struct AmbientLight
        : public Light {
    Color Lout;

public:
    AmbientLight() {
        Lout = Color( 1, 1, 1 );
    }

    virtual ~AmbientLight() {};

    Color getIntensity( Vector &targetPoint ) {
        return Lout;
    }

    Vector getDirection( Vector &targetPoint ) {
        return Vector( 0, 0, 0 );
    }

    Number getDistance( Vector &targetPoint ) {
        return Number( 0 );
    }
};

#endif //CYLINDERS_AMBIENTLIGHT_H
