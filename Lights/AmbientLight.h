//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_AMBIENTLIGHT_H
#define CYLINDERS_AMBIENTLIGHT_H


#include "Light.h"

struct AmbientLight
        : public Light {
    Color Lout;

    AmbientLight() {
        Lout = Color( 1, 1, 1 );
    }

    virtual ~AmbientLight() {};

    Color getIntensity( Vector &targetPoint ) {
        return Lout;
    }

    Vector getDirection( Vector &targetPoint ) {
        return Vector( 0, 0, 0 );float
    }

    Number getDistance( Vector &targetPoint ) {
        return 0;
    }

    Light *clone() {
        return new AmbientLight( *this );
    }

    bool isPointLight() {
        return false;
    };
};

#endif //CYLINDERS_AMBIENTLIGHT_H
