#pragma once

#include "Materials/Material.h"
#include "MathUtils/Matrix.h"

struct Ray;
struct RayHit;

struct ObjectPosition {
    Vector origo;
    Vector yAxis;

    ObjectPosition() {}

    ObjectPosition(const Vector &origo_init, const Vector &yAxis_init)
        : origo(origo_init), yAxis(yAxis_init) {}
};

class Object {
  protected:
    Matrix transform, inverseTransform;
    Matrix scalem, rotate, shift, inversScale, inverseRotate, inverseShift;

  public:
    Material *material;

    Object(Material *material_init);

    virtual ~Object();

    virtual Number intersect(Ray &r, RayHit &hit) = 0;

    virtual Vector getNormalAtPoint(Vector &intersectPoint) = 0;

    virtual Color getKD(const Vector &intersectPoint);

    virtual Color getKA(const Vector &intersectPoint);

    virtual Color getKS();

    Number getShininess();

    Ray convertRayToObjectCoords(Ray &r);

    ObjectPosition convertPositionToWordCoords(ObjectPosition &op);

    void clearTransform();

    void setScale(Number scale);

    void setScale(Number scaleX, Number scaleY, Number scaleZ);

    void setRotateX(Number fi);

    void setRotateY(Number fi);

    void setRotateZ(Number fi);

    void setRotate(Number xfi, Number yfi, Number zfi);

    void setShift(Vector pos);

    void setNewBasesAndOrigo(Vector &newY, Vector &newOrigo);

  protected:
    Vector convertToObjectCoords(Vector v);

    Vector convertToWorldsCoords(Vector v);
};
