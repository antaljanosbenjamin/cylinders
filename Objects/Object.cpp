//
// Created by kovi on 4/16/17.
//

#include "Object.h"

virtual Object::~Object() {};

Ray Object::convertRayToObjectCoords( Ray &r ) {
    return Ray( convertToObjectCoords( r.source ), convertToObjectCoords( r.source + r.direction ) - convertToObjectCoords( r.source ));
}

ObjectPosition Object::convertPositionToWordCoords( ObjectPosition &op ) {
    Vector origoInWorld = convertToWorldsCoords( op.origo );
    return ObjectPosition( origoInWorld, convertToWorldsCoords( op.yAxis ) - origoInWorld );
}


void Object::clearTransform() {
    transform.loadIdentity();
    inverseTransform.loadIdentity();
}

Vector Object::convertToObjectCoords( Vector v ) {
    return v * inverseTransform;
}

Vector Object::convertToWorldsCoords( Vector v ) {
    return v * transform;
}

void Object::setScale( float scale ) {
    Matrix scaleMatrix;
    scaleMatrix.loadIdentity();
    scaleMatrix.matrix[0][0] = scaleMatrix.matrix[1][1] = scaleMatrix.matrix[2][2] = scale;
    scalem = scaleMatrix;
    transform = transform * scaleMatrix;
    scaleMatrix.matrix[0][0] = scaleMatrix.matrix[1][1] = scaleMatrix.matrix[2][2] = 1 / scale;

    inversScale = scaleMatrix;
    inverseTransform = scaleMatrix * inverseTransform;
}

void Object::setScale( float scaleX, float scaleY, float scaleZ ) {
    Matrix scaleMatrix;
    scaleMatrix.loadIdentity();
    scaleMatrix.matrix[0][0] = scaleX;
    scaleMatrix.matrix[1][1] = scaleY;
    scaleMatrix.matrix[2][2] = scaleZ;
    transform = transform * scaleMatrix;
    scaleMatrix.matrix[0][0] = 1 / scaleX;
    scaleMatrix.matrix[1][1] = 1 / scaleY;
    scaleMatrix.matrix[2][2] = 1 / scaleZ;
    inverseTransform = scaleMatrix * inverseTransform;
}

void Object::setRotateX( float fi ) {
    float cosfi = cos( fi );
    float sinfi = sin( fi );
    Matrix rotateMatrix;
    rotateMatrix.loadIdentity();
    rotateMatrix.matrix[1][1] = rotateMatrix.matrix[2][2] = cosfi;
    rotateMatrix.matrix[2][1] = -sinfi;
    rotateMatrix.matrix[1][2] = sinfi;
    transform = transform * rotateMatrix;
    rotate = rotateMatrix;
    rotateMatrix.matrix[1][1] = rotateMatrix.matrix[2][2] = cos( -fi );
    rotateMatrix.matrix[1][2] = -sinfi;
    rotateMatrix.matrix[2][1] = sinfi;
    inverseRotate = rotateMatrix;
    inverseTransform = rotateMatrix * inverseTransform;
}

void Object::setRotateY( float fi ) {
    float cosfi = cos( fi );
    float sinfi = sin( fi );
    Matrix rotateMatrix;
    rotateMatrix.loadIdentity();
    rotateMatrix.matrix[0][0] = rotateMatrix.matrix[2][2] = cosfi;
    rotateMatrix.matrix[0][2] = -sinfi;
    rotateMatrix.matrix[2][0] = sinfi;
    transform = transform * rotateMatrix;
    rotate = rotateMatrix;
    rotateMatrix.matrix[0][0] = rotateMatrix.matrix[2][2] = cos( -fi );
    rotateMatrix.matrix[2][0] = -sinfi;
    rotateMatrix.matrix[0][2] = sinfi;
    inverseRotate = rotateMatrix;
    inverseTransform = rotateMatrix * inverseTransform;
}

void Object::setRotateZ( float fi ) {
    float cosfi = cos( fi );
    float sinfi = sin( fi );
    Matrix rotateMatrix;
    rotateMatrix.loadIdentity();
    rotateMatrix.matrix[0][0] = rotateMatrix.matrix[1][1] = cosfi;
    rotateMatrix.matrix[1][0] = -sinfi;
    rotateMatrix.matrix[0][1] = sinfi;
    transform = transform * rotateMatrix;
    rotate = rotateMatrix;
    rotateMatrix.matrix[0][0] = rotateMatrix.matrix[1][1] = cos( -fi );
    rotateMatrix.matrix[0][1] = -sinfi;
    rotateMatrix.matrix[1][0] = sinfi;
    inverseRotate = rotateMatrix;
    inverseTransform = rotateMatrix * inverseTransform;
}

void Object::setRotate( float xfi, float yfi, float zfi ) {
    setRotateZ( zfi );
    setRotateY( yfi );
    setRotateX( xfi );
}

void Object::setShift( Vector pos ) {
    Matrix shiftMatrix;
    shiftMatrix.loadIdentity();
    shiftMatrix.matrix[3][0] = pos.getX();
    shiftMatrix.matrix[3][1] = pos.getY();
    shiftMatrix.matrix[3][2] = pos.getZ();
    shift = shiftMatrix;
    transform = transform * shiftMatrix;

    shiftMatrix.matrix[3][0] = -pos.getX();
    shiftMatrix.matrix[3][1] = -pos.getY();
    shiftMatrix.matrix[3][2] = -pos.getZ();
    inverseShift = shiftMatrix;
    inverseTransform = shiftMatrix * inverseTransform;
}

void Object::setNewBasesAndOrigo( Vector &newY, Vector &newOrigo ) {
    Vector newX = newY.rotateByZ( M_PI / 2 );
    Vector newZ = newX % newY;
    newX = newX.getNormalized();
    newY = newY.getNormalized();
    newZ = newZ.getNormalized();
    Matrix newBaseMatrix;
    newBaseMatrix.loadIdentity();
    newBaseMatrix.matrix[0][0] = newX.getX();
    newBaseMatrix.matrix[0][1] = newX.getY();
    newBaseMatrix.matrix[0][2] = newX.getZ();
    newBaseMatrix.matrix[1][0] = newY.getX();
    newBaseMatrix.matrix[1][1] = newY.getY();
    newBaseMatrix.matrix[1][2] = newY.getZ();
    newBaseMatrix.matrix[2][0] = newZ.getX();
    newBaseMatrix.matrix[2][1] = newZ.getY();
    newBaseMatrix.matrix[2][2] = newZ.getZ();
    newBaseMatrix.matrix[3][0] = newOrigo.getX();
    newBaseMatrix.matrix[3][1] = newOrigo.getY();
    newBaseMatrix.matrix[3][2] = newOrigo.getZ();

    transform = transform * newBaseMatrix;

    newBaseMatrix.loadIdentity();
    newBaseMatrix.matrix[0][0] = newX.getX();
    newBaseMatrix.matrix[1][0] = newX.getY();
    newBaseMatrix.matrix[2][0] = newX.getZ();
    newBaseMatrix.matrix[0][1] = newY.getX();
    newBaseMatrix.matrix[1][1] = newY.getY();
    newBaseMatrix.matrix[2][1] = newY.getZ();
    newBaseMatrix.matrix[0][2] = newZ.getX();
    newBaseMatrix.matrix[1][2] = newZ.getY();
    newBaseMatrix.matrix[2][2] = newZ.getZ();

    inverseTransform = newBaseMatrix * inverseTransform;

    newBaseMatrix.loadIdentity();
    newBaseMatrix.matrix[3][0] = -newOrigo.getX();
    newBaseMatrix.matrix[3][1] = -newOrigo.getY();
    newBaseMatrix.matrix[3][2] = -newOrigo.getZ();

    inverseTransform = newBaseMatrix * inverseTransform;
}