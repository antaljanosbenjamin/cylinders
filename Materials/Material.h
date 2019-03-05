#pragma once

#include "../MathUtils/Vector.h"
#include "Color.h"

enum MaterialType
{
    ROUGH = 1,
    REFLECTIVE = 2,
    REFRACTIVE = 4
};

class Material
{
  protected:
    Number n;
    Number shine;
    Color F0;
    Color kd;
    Color ks;
    Color ka;
    MaterialType type;

  public:
    Material(Number n_init, Number shine_init, Color F0_init, Color kd_init, Color ks_init, MaterialType type_init);

    virtual Material *clone();

    static Color makeF0(Color &colorN, Color &colorK);

    Color Fresnel(Vector view, Vector normal);

    bool isReflective();

    bool isRefractive();

    bool isRough();

    Vector reflect(Vector view, Vector normal);

    bool refract(Vector view, Vector normal, Vector &refractedRay);

    virtual Color getKD(const Vector &v);

    virtual Color getKA(const Vector &v);

    virtual Color getKS();

    virtual Number getShineness();
};
