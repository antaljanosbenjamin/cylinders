#pragma once

#include <cstdlib>
#include <functional>

#include "Material.h"
#include "../MathUtils/Number.h"
#include "../MathUtils/Vector.h"

typedef std::function<Color(const Vector &)> KAFunction;

typedef std::function<Color(const Vector &)> KDFunction;

class TableMaterial
    : public Material
{

    KAFunction m_getKAFunction;

    KDFunction m_getKDFunction;

  public:
    TableMaterial(Number n_init, Number shine_init, Color F0_init, Color kd_init, Color ks_init, MaterialType type_init, KAFunction getKAFunction,
                  KDFunction getKDFunction);

    virtual Color getKA(const Vector &v);

    virtual Color getKD(const Vector &v);
};
