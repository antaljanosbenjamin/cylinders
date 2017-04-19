//
// Created by kovi on 4/16/17.
//

#include "InfiniteCylinder.h"

InfiniteCylinder::InfiniteCylinder( Material *material_init, Number radius_init )
        : Object( material_init ), radius( radius_init ) {};

InfiniteCylinder::~InfiniteCylinder() {}

// Világ koordinátákban lévő vektort kap
Vector InfiniteCylinder::getNormalAtPoint( Vector &intersectPoint ) {
    Vector ownIntersectPoint( convertToObjectCoords( intersectPoint ));
    return intersectPoint - convertToWorldsCoords( Vector( Number( 0 ), ownIntersectPoint.getY(), Number( 0 ) ));
}

Number InfiniteCylinder::intersect( Ray &r, RayHit &hit ) {
    Ray ownRay( convertRayToObjectCoords( r ));

    Vector dir2D = ownRay.direction;
    dir2D.setY( Number( 0 ) );
    Vector source2D = ownRay.source;
    source2D.setY( Number( 0 ) );

    Number tNew( -1 );

    // Palást
    Number a = dir2D * dir2D;
    Number b = 2 * dir2D * source2D;
    Number c = source2D * source2D - npow( radius, 2 );
    if( a != 0.0f ){
        Number determinant = b * b - 4 * a * c;
        if( determinant == 0.0f ){
            Number triedT = -b / ( 2 * a );
            tNew = triedT;
        }
        else if( determinant > 0.0f ){
            Number x1 = ( -b + nsqrt( determinant )) / ( 2.0f * a );
            Number x2 = ( -b - nsqrt( determinant )) / ( 2.0f * a );

            Vector intersect1 = ownRay.source + x1 * ownRay.direction;
            Vector intersect2 = ownRay.source + x2 * ownRay.direction;
            if( x1 < x2 || x2 < 0.0f )
                tNew = x1;
            else
                tNew = x2;
        }
    }

    if( tNew > 0 ){
        return tNew;
    }
    return Number( -1.0f );
}

