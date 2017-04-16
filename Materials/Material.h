//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_MATERIAL_H
#define CYLINDERS_MATERIAL_H



enum MaterialType{
    ROUGH = 1,
    REFLECTIVE = 2,
    REFRACTIVE = 4,
    BOTH = 8,
    REFLECTIVE_AND_BOTH = 10,
    REFRACTIVE_AND_BOTH = 12
};

struct Material{
    float n, shine;
    Color F0, kd, ks, ka;
    MaterialType type;

    Material(float n_init, float shine_init, Color F0_init, Color kd_init, Color ks_init, MaterialType type_init)
            :n(n_init), shine(shine_init), F0(F0_init), kd(kd_init), ks(ks_init), ka(kd_init*2.0f), type(type_init) {};

    //virtual ~Material(){};

    virtual Material* clone(){
        return this;
    }

    static Color makeF0(Color& colorN, Color& colorK){
        return ((colorN - 1)*(colorN - 1) + colorK*colorK) / ((colorN + 1)*(colorN + 1) + colorK*colorK);
    }

    Color Fresnel(Vector view, Vector normal){
        float cosa = fabs(normal * view);
        return  F0 + (Color(1.0f, 1.0f, 1.0f) - F0) * pow(1 - cosa, 5);
    }
    bool isReflective(){
        return (REFLECTIVE_AND_BOTH & type) > 0;
    }

    bool isRefractive(){
        return (REFRACTIVE_AND_BOTH & type) > 0;
    }

    bool isRough(){
        return (type & ROUGH) > 0;
    }

    Vector reflect(Vector view, Vector normal){
        Vector ret = view - (2 * normal*(normal*view));

        //std::cout << ret.x << "   " << ret.y << "   " << ret.z << std::endl;
        return ret;
    }

    bool refract(Vector view, Vector normal, Vector& refractedRay){
        float cosa = -(normal * view);
        float cn = n;
        if (cosa < 0){
            cosa = -cosa;
            cn = 1 / cn;
            normal = -1 * (normal);
        }
        float disc = 1 - (1 - cosa * cosa) / cn / cn;
        if (disc < 0) return false;
        refractedRay = (view / cn + normal * (cosa / cn - sqrt(disc))).normalize();

        return true;
    }

    virtual Color getKD(Vector& v){
        return kd;
    }

    virtual Color getKA(Vector& v){
        return ka;
    }
};


#endif //CYLINDERS_MATERIAL_H
