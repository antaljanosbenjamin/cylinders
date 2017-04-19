//
// Created by kovi on 4/19/17.
//

#ifndef CYLINDERS_POINTLIGHT_H
#define CYLINDERS_POINTLIGHT_H

#include "Light.h"

struct PointLight
        : public Light {
    Vector position;
    Color Lout;

    PointLight()
            : position( Vector( 0.0f, 0.0f, 0.0f )), Lout( Color( 0.0f, 0.0f, 0.0f )) {};

    virtual ~PointLight() {};

    PointLight( Vector position_init, Color Lout_init )
            : position( position_init ), Lout( Lout_init ) {};

    Color getIntensity( Vector &targetPoint ) {
        return Lout * ( 1 / npow( position.getDistance( targetPoint ), 1.4f ));
    }

    Vector getDirection( Vector &targetPoint ) {
        return position - targetPoint;
    }

    Number getDistance( Vector &targetPoint ) {
        return ( position - targetPoint ).length();
    }
};

#endif //CYLINDERS_POINTLIGHT_H
