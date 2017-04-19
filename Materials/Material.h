//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_MATERIAL_H
#define CYLINDERS_MATERIAL_H


#include "../MathUtils/Vector.h"
#include "Color.h"

enum MaterialType {
    ROUGH = 1,
    REFLECTIVE = 2,
    REFRACTIVE = 4,
    BOTH = 8,
    REFLECTIVE_AND_BOTH = 10,
    REFRACTIVE_AND_BOTH = 12
};

struct Material {
    Number n, shine;
    Color F0, kd, ks, ka;
    MaterialType type;

    Material( Number n_init, Number shine_init, Color F0_init, Color kd_init, Color ks_init, MaterialType type_init );
    //virtual ~Material(){};

    virtual Material *clone();

    static Color makeF0( Color &colorN, Color &colorK );

    Color Fresnel( Vector view, Vector normal );

    bool isReflective();

    bool isRefractive();

    bool isRough();

    Vector reflect( Vector view, Vector normal );

    bool refract( Vector view, Vector normal, Vector &refractedRay );

    virtual Color getKD( const Vector &v );

    virtual Color getKA( const Vector &v );
};


#endif //CYLINDERS_MATERIAL_H
