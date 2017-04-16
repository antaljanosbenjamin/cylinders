//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_TABLEMATERIAL_H
#define CYLINDERS_TABLEMATERIAL_H


#include "Material.h"
#include "../MathUtils/Number.h"
#include "../MathUtils/Vector.h"

struct TableMaterial
        : public Material {

    TableMaterial( Number n_init, Number shine_init, Color F0_init, Color kd_init, Color ks_init, MaterialType type_init )
            : Material( n_init, shine_init, F0_init, kd_init, ks_init, type_init ) {
        ka = ka * 0.5f;
    };

    //virtual ~TableMaterial(){};

    virtual Color getKA( Vector &v ) {
        int x = (int) abs( v.getX() / 4 );
        int z = (int) abs( v.getZ() / 4 );
        if( v.getX() < 0.0f )
            x++;
        if( v.getZ() < 0.0f )
            z++;
        x = x % 2;
        z = z % 2;
        Color ret(( x * 0.5f + 0.5f ) / 2.0f, 0.2f, ( z * 0.5f + 0.3f ) / 2.0f );
        return ret;
    }

    virtual Material *clone() {
        return new TableMaterial( *this );
    }

    virtual Color getKD( Vector &v ) {
        Color ret = getKA( v );
        return ret;
    }
};


#endif //CYLINDERS_TABLEMATERIAL_H
