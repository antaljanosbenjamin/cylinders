//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_OBJECT_H
#define CYLINDERS_OBJECT_H

#include "../Utils/Matrix.h"

struct Ray;
struct RayHit;

struct Material;


struct ObjectPosition {
    Vector origo;
    Vector yAxis;

    ObjectPosition() {}

    ObjectPosition( const Vector &origo_init, const Vector &yAxis_init )
            : origo( origo_init ), yAxis( yAxis_init ) {}

};


class Object {
    Matrix transform, inverseTransform;
    Matrix scalem, rotate, shift, inversScale, inverseRotate, inverseShift;
    Material *material;

    virtual ~Object();

    virtual float intersect( Ray &r, RayHit &hit ) = 0;

    virtual Vector getNormalAtPoint( Vector &intersectPoint ) = 0;


    Ray convertRayToObjectCoords( Ray &r );

    ObjectPosition convertPositionToWordCoords( ObjectPosition &op );

    void clearTransform();

    void setScale( float scale );

    void setScale( float scaleX, float scaleY, float scaleZ );

    void setRotateX( float fi );

    void setRotateY( float fi );

    void setRotateZ( float fi );

    void setRotate( float xfi, float yfi, float zfi );

    void setShift( Vector pos );

    void setNewBasesAndOrigo( Vector &newY, Vector &newOrigo );

private:
    Vector convertToObjectCoords( Vector v );

    Vector convertToWorldsCoords( Vector v );
};


#endif //CYLINDERS_OBJECT_H
