#pragma once

#include <memory>

#include "../MathUtils/Vector.h"

class Object;

struct Ray {
    Vector source, direction;

    Ray()
            : source( Vector( 0.0f, 0.0f, 0.0f )), direction( Vector( 0.0f, 0.0f, 0.0f )) {};

    Ray( const Vector &source_init, const Vector &direction_init )
            : source( source_init ), direction( direction_init ) {};
};

struct RayHit {
    Object *hittedObject;
    Number hittingTime;
    Vector intersectPoint

#ifdef DEBUG
    , intersectPoint2
#endif
    ;
    Vector normal;
};
