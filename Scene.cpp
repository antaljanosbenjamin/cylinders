//
// Created by kovi on 4/16/17.
//

#include "Scene.h"

Scene::Scene( Camera cam_init, int screenW, int screenH, Color *img )
        : cam( cam_init ), screenWidth( screenW ), screenHeight( screenH ), image( img ), lightsNum( 0 ), objectsNum( 0 ) {
}

Scene::~Scene() {
    for( int i = 0; i < objectsNum; i++ ){
        delete objects[i];
    }
    for( int i = 0; i < lightsNum; i++ ){
        delete lights[i];
    }
}

void Scene::addObject( Object *obj ) {
    objects[objectsNum++] = obj;
}

void Scene::addLight( Light *light ) {
    lights[lightsNum++] = light;
}

void Scene::render() {
    for( int i = 0; i < screenWidth; i++ ){
        //std::cout << "i: " << i << std::endl;
        for( int j = 0; j < screenHeight; j++ ){
            Ray ray = cam.getRay( i, j );
            Color returnColor = trace( ray, 0 );
            /*if (!(returnColor.r > -1.0f))
            returnColor = image[j*screenWidth + i - 1];*/
            image[j * screenWidth + i] = returnColor;
        }
    }
}

RayHit Scene::intersectAll( Ray &r ) {
    RayHit hit;
    hit.hittingTime = -1.0f;
    for( int i = 0; i < objectsNum; i++ ){
        Number tNew = objects[i]->intersect( r, hit );
        if( tNew >= 0 && ( tNew < hit.hittingTime || hit.hittingTime < 0 )){
            hit.hittedObject = objects[i];
            hit.hittingTime = tNew;
        }
    }
    return hit;
}

Color Scene::trace( Ray &r, int d ) {
    if( d >= 15 )
        return ambientLight.Lout;
    RayHit hit = intersectAll( r );
    if( hit.hittingTime > 0.0f ){
        hit.intersectPoint = r.source + r.direction * hit.hittingTime;
        hit.normal = hit.hittedObject->getNormalAtPoint( hit.intersectPoint ).getNormalized();
        /* Azért nem lehet itt, mert akkor nem tudjuk, a refractban, hogy belülről vagy kívülről megyünk. Ezért kell a Rough/reflective
        blokkon belülre rakni.
        if (hit.normal * r.direction > 0){
        hit.normal = hit.hittedObject->getNormalAtPoint(hit.intersectPoint).getNormalized();
        //hit.normal = -1.0f * hit.normal;
        }*/
        Color ret( 0.0f, 0.0f, 0.0f );
        if( hit.hittedObject->material->isRough()){
            //return Color(0, 1, 0);
            Color ka = hit.hittedObject->material->getKA( hit.intersectPoint );
            ret = ka * ambientLight.Lout;
            for( int i = 0; i < lightsNum; i++ ){
                Vector shadowDir(( lights[i]->getDirection( hit.intersectPoint )));
                Ray shadowRay( hit.intersectPoint + shadowDir.getNormalized() * 0.01f, shadowDir );
                RayHit shadowHit = intersectAll( shadowRay );
                if( shadowHit.hittingTime < 0.0f ||
                    ( shadowHit.hittingTime * shadowRay.direction ).length() >= lights[i]->getDistance( hit.intersectPoint )){
                    Color intensity = lights[i]->getIntensity( hit.intersectPoint );
                    Color kd = hit.hittedObject->getKD( hit.intersectPoint );
                    Color ks = hit.hittedObject->getKS();
                    Number shine = hit.hittedObject->material->shine;
                    Number cosa = ( shadowRay.direction.getNormalized() & hit.normal );
                    Vector h = ( shadowRay.direction.getNormalized() - r.direction.getNormalized()).getNormalized();
                    Number cosh = ( h & hit.normal );
                    Color plusDiffuse = intensity * kd * cosa;
                    Color plusSpecular = intensity * ks * npow( cosh, shine );
                    ret = ret + plusDiffuse + plusSpecular;
                }
            }
        }
        else{
            if( hit.hittedObject->material->isReflective()){
                Vector reflectedDir = hit.hittedObject->material->reflect( r.direction.getNormalized(), hit.normal ).getNormalized();
                Color F = hit.hittedObject->material->Fresnel( r.direction.getNormalized(), hit.normal );
                Ray reflectedRay( hit.intersectPoint + 0.01f * reflectedDir, reflectedDir.getNormalized());
                ret = ret + F * trace( reflectedRay, d + 1 );
            }
            if( hit.hittedObject->material->isRefractive()){
                Vector refractedDir;
                if( hit.hittedObject->material->refract( r.direction.getNormalized(), hit.normal, refractedDir )){
                    Color F = hit.hittedObject->material->Fresnel( r.direction.getNormalized(), hit.normal );
                    Ray refractedRay( hit.intersectPoint + 0.01f * refractedDir, refractedDir );
                    Color traced = trace( refractedRay, d + 1 );
                    Color plus = ( Color( 1.0f, 1.0f, 1.0f ) - F ) * traced;
                    ret = ret + plus;

                }
                else{
                    Vector reflectedDir = hit.hittedObject->material->reflect( r.direction.getNormalized(), hit.normal ).getNormalized();
                    Ray reflectedRay( hit.intersectPoint + 0.01f * reflectedDir, reflectedDir );
                    Color traced = trace( reflectedRay, d + 1 );
                    ret = ret + traced;
                }
            }
        }
        Number maxI = ret.getMaxIntensity();
        if( maxI > 1.0f ){
            ret = ret / maxI;
        }
        //ret = ret * luminanceComma / luminance;
        if( !( ret.r > 0 && ret.g > 0 && ret.b > 0 )){
            hit.normal = hit.hittedObject->getNormalAtPoint( hit.intersectPoint ).getNormalized();
        }
        return ret;
    }
    return ambientLight.Lout;
}

void Scene::build() {

    ambientLight.Lout = Color( 0.7f, 0.7f, 1.0f );

    // Asztal
    // TODO az objektumnak getKA/KD függvényt csinálni

    Material *pink = new TableMaterial( Number( 0 ), Number( 5 ), Color( 0.0f, 0.0f, 0.0f ), Color( 1.0f, 0.3f, 0.3f ) / 2, Color( 0.3, 0.3, 0.3 ), ROUGH );
    Plane *table = new Plane( pink, Number( 100 ), Number( 100 ) );
    addObject( table );


//        Color silverN = Color(0.14f, 0.16f, 0.13f);
//        Color silverK = Color(4.1f, 2.4f, 3.1f);
//        Color silverF0 = Material::makeF0(silverN, silverK);
//        Material *silver = new Material(0, 0, silverF0, Color(0,0,0), Color(0,0,0), REFLECTIVE);
//
//        Color goldN = Color(0.17f, 0.35f, 1.5f);
//        Color goldK = Color(3.1f, 2.7f, 1.9f);
//        Color goldF0 = Material::makeF0(goldN, goldK);
//        Material gold = Material(0, 0, goldF0, Color(0,0,0), Color(0,0,0), REFLECTIVE);


    Color glassN = Color( 1.5f, 1.5f, 1.5f );
    Color glassK = Color( 0.0f, 0.0f, 0.0f );
    Color glassF0 = Material::makeF0( glassN, glassK );
    Material *glass = new Material( Number( 1.5f ), Number( 0 ), glassF0, Color( 0, 0, 0 ), Color( 0, 0, 0 ), REFRACTIVE );

    InfiniteCylinder *cylinder = new InfiniteCylinder( glass, Number( 10.0 ));
    cylinder->setRotateZ( Number( M_PI / 4 ) );
    addObject( cylinder );
}
