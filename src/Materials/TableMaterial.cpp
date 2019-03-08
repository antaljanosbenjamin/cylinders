#include "Materials/TableMaterial.h"

TableMaterial::TableMaterial(Number n_init, Number shine_init, Color F0_init, Color kd_init,
                             Color ks_init, MaterialType type_init, KAFunction getKAFunction,
                             KDFunction getKDFunction)
    : Material(n_init, shine_init, F0_init, kd_init, ks_init, type_init),
      m_getKAFunction(getKAFunction), m_getKDFunction(getKDFunction) {
    ka = ka * 0.5f;
};

Color TableMaterial::getKA(const Vector &v) { return m_getKAFunction(v); }

Color TableMaterial::getKD(const Vector &v) { return m_getKDFunction(v); }