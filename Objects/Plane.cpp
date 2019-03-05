#include <cstdlib>

#include "Plane.h"

Plane::Plane(Material *mat, Number width_init, Number depth_init)
    : Object(mat), normal(Vector(0.0f, 1.0f, 0.0f)), width(width_init), depth(depth_init), widthPer2(width / 2.0f), depthPer2(depth / 2.0f){};

Plane::~Plane() {}

Vector Plane::getNormalAtPoint(Vector &intersectPoint)
{
    Vector ownIntersectPoint(convertToObjectCoords(intersectPoint));
    if (planeContains(ownIntersectPoint))
        return (normal * transform) - (Vector(0, 0, 0) * transform);
    else
        return Vector(0, 0, 0);
}

ObjectPosition Plane::getPositionByUV(Number u, Number v)
{
    u -= 0.5f;
    v -= 0.5f;
    Vector origo(u * width, Number(0), v * depth);
    Vector normal(0.0f, 1.0f, 0.0f);
    ObjectPosition op(origo, normal);
    return convertPositionToWordCoords(op);
}

bool Plane::planeContains(Vector v)
{
    if (v * normal == 0.0f && nabs(v.getZ()) <= depthPer2 && nabs(v.getX()) <= widthPer2)
        return true;
    else
        return false;
}

Number Plane::intersect(Ray &r, RayHit &hit)
{
    Ray ownRay(convertRayToObjectCoords(r));
    if (ownRay.direction.getY() != 0)
    {
        Number tNew = -(ownRay.source * normal) / (ownRay.direction * normal);
        Vector intersectPoint = (ownRay.source + tNew * ownRay.direction);
        if (tNew >= 0.0f && planeContains(intersectPoint))
            return tNew;
    }

    return Number(-1.0);
}