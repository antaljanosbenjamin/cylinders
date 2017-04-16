//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_TABLEMATERIAL_H
#define CYLINDERS_TABLEMATERIAL_H

#include <cstdlib>

#include "Material.h"
#include "../MathUtils/Number.h"
#include "../MathUtils/Vector.h"


struct TableMaterial
        : public Material {

    TableMaterial( Number n_init, Number shine_init, Color F0_init, Color kd_init, Color ks_init, MaterialType type_init );

    //virtual ~TableMaterial(){};

    virtual Color getKA( Vector &v );

    virtual Color getKD( Vector &v );
};


#endif //CYLINDERS_TABLEMATERIAL_H
