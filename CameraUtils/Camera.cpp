#include "Camera.h"

Camera::Camera(const Vector &eye_init, const Vector &lookat_init, const Vector &up_init, Number xMax_init, Number yMax_init)
    : eye(eye_init), lookat(lookat_init), up(up_init), xMax(xMax_init), yMax(yMax_init)
{
    right = (lookat - eye) % up;
    up = right % (lookat - eye);
    right = right.getNormalized() * 15 * (xMax / yMax);
    up = up.getNormalized() * 15;
}

void Camera::setNewEyeAndLookat(const Vector &e, const Vector &l, const Vector &u)
{
    eye = e;
    lookat = l;
    up = u;
    right = (lookat - eye) % up;
    up = right % (lookat - eye);
    right = right.getNormalized() * 15 * (xMax / yMax);
    up = up.getNormalized() * 15;
}

Ray Camera::getRay(double xPos, double yPos)
{
    Vector dir((lookat + (up * (yPos - (yMax / 2)) / (yMax / 2) + right * (xPos - (xMax / 2)) / (xMax / 2)) - eye).getNormalized());
    return Ray(eye, dir);
}