//
// Created by kovi on 4/16/17.
//

#include "Material.h"

Material::Material(Number n_init, Number shine_init, Color F0_init, Color kd_init, Color ks_init, MaterialType type_init)
    : n(n_init), shine(shine_init), F0(F0_init), kd(kd_init), ks(ks_init), ka(kd_init * 2.0f), type(type_init){};

Material *Material::clone()
{
    return this;
}

Color Material::makeF0(Color &colorN, Color &colorK)
{
    return ((colorN - 1) * (colorN - 1) + colorK * colorK) / ((colorN + 1) * (colorN + 1) + colorK * colorK);
}

Color Material::Fresnel(Vector view, Vector normal)
{
    Number cosa(nabs(normal * view));
    return F0 + (Color(1.0f, 1.0f, 1.0f) - F0) * npow(1 - cosa, 5);
}

bool Material::isReflective()
{
    return (REFLECTIVE & type) > 0;
}

bool Material::isRefractive()
{
    return (REFRACTIVE & type) > 0;
}

bool Material::isRough()
{
    return (type & ROUGH) > 0;
}

Vector Material::reflect(Vector view, Vector normal)
{
    Vector ret = view - (2 * normal * (normal * view));

    //std::cout << ret.x << "   " << ret.y << "   " << ret.z << std::endl;
    return ret;
}

bool Material::refract(Vector view, Vector normal, Vector &refractedRay)
{
    Number cosa = -(normal * view);
    Number cn = n;
    if (cosa < 0)
    {
        cosa = -cosa;
        cn = 1 / cn;
        normal = -1 * (normal);
    }
    Number disc = 1 - (1 - cosa * cosa) / cn / cn;
    if (disc < 0)
        return false;
    refractedRay = (view / cn + normal * (cosa / cn - nsqrt(disc))).getNormalized();

    return true;
}

Color Material::getKD(const Vector &v)
{
    return kd;
}

Color Material::getKA(const Vector &v)
{
    return ka;
}

Color Material::getKS()
{
    return ks;
}

Number Material::getShineness()
{
    return shine;
}