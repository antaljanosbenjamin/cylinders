//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_TABLEMATERIAL_H
#define CYLINDERS_TABLEMATERIAL_H

#include <cstdlib>
#include <functional>

#include "Material.h"
#include "../MathUtils/Number.h"
#include "../MathUtils/Vector.h"

typedef std::function<Color( const Vector & )> KAFunction;
typedef std::function<Color( const Vector & )> KDFunction;

class TableMaterial
        : public Material {

    KAFunction m_getKAFunction;

    KDFunction m_getKDFunction;

public:
    TableMaterial( Number n_init, Number shine_init, Color F0_init, Color kd_init, Color ks_init, MaterialType type_init, KAFunction getKAFunction,
                   KDFunction getKDFunction );

    //virtual ~TableMaterial(){};

    virtual Color getKA( const Vector &v );

    virtual Color getKD( const Vector &v );
};


#endif //CYLINDERS_TABLEMATERIAL_H
