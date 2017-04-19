//
// Created by kovi on 4/16/17.
//

#include <iostream>
#include "Scene.h"

int Scene::TRACE_DEPTH = 5;

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
    for( int xPos = 0; xPos < screenWidth; xPos++ ){
        for( int yPos = 0; yPos < screenHeight; yPos++ ){
            Ray ray = cam.getRay( xPos, yPos );
            Color returnColor = trace( ray, 0 );
            image[yPos * screenWidth + xPos] = returnColor;
        }
    }
    smoothOutEdges();
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
    if( d >= TRACE_DEPTH )
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

    KDFunction squaredKD = []( const Vector &v ) {
        int x = nabs( v.getX() / 4.0 ).value;
        int z = nabs( v.getZ() / 4 ).value;
        if( v.getX() < 0.0f )
            x++;
        if( v.getZ() < 0.0f )
            z++;
        x = x % 2;
        z = z % 2;
        Color ret(( x * 0.5f + 0.5f ) / 2.0f, 0.2f, ( z * 0.5f + 0.3f ) / 2.0f );
        return ret;
    };

    KDFunction diagonalKD = []( const Vector &v ) {
        Vector copy = v.rotateByY( Number( M_PI / 4 ));
        int x = nabs( copy.getX() / 4.0 ).value;
        int z = nabs( copy.getZ() / 4 ).value;
        if( copy.getX() < 0.0f )
            x++;
        if( copy.getZ() < 0.0f )
            z++;
        x = x % 2;
        z = z % 2;
        Color ret(( x * 0.2f + 0.1f ) / 2.0f, 0.8f, ( z * 1.6f + 0.3f ) / 2.0f );
        return ret;
    };

    KDFunction cylinderKD = []( const Vector &v ) {
        Vector copy = v.rotateByY( Number( M_PI / 4 ));
        return Color( nsin( v.getX() * 1.1 ), ncos( copy.getX() * 0.8 ), ncos( v.getZ()));
    };

    Material *diagonal = new TableMaterial( Number( 0 ), Number( 5 ), Color( 0.0f, 0.0f, 0.0f ), Color( 1.0f, 0.3f, 0.3f ) / 2, Color( 0.3, 0.3, 0.3 ), ROUGH,
                                            diagonalKD, diagonalKD );

    Material *squared = new TableMaterial( Number( 0 ), Number( 5 ), Color( 0.0f, 0.0f, 0.0f ), Color( 1.0f, 0.3f, 0.3f ) / 2, Color( 0.3, 0.3, 0.3 ), ROUGH,
                                           squaredKD, squaredKD );

    Material *cylinderMaterial = new TableMaterial( Number( 0 ), Number( 5 ), Color( 0.0f, 0.0f, 0.0f ), Color( 1.0f, 0.3f, 0.3f ) / 2, Color( 0.3, 0.3, 0.3 ),
                                                    ROUGH,
                                                    cylinderKD, cylinderKD );

    Plane *bottom = new Plane( squared, Number( 100 ), Number( 100 ));
    addObject( bottom );

    Plane *top = new Plane( diagonal, Number( 100 ), Number( 100 ));
    top->setRotateZ( Number( M_PI ));
    top->setShift( Vector( 0, 25, 0 ));
    addObject( top );


    Color silverN = Color( 0.14f, 0.16f, 0.13f );
    Color silverK = Color( 4.1f, 2.4f, 3.1f );
    Color silverF0 = Material::makeF0( silverN, silverK );
    Material *silver = new Material( Number( 0 ), Number( 0 ), silverF0, Color( 0, 0, 0 ), Color( 0, 0, 0 ), REFLECTIVE );

    Color goldN = Color( 0.17f, 0.35f, 1.5f );
    Color goldK = Color( 3.1f, 2.7f, 1.9f );
    Color goldF0 = Material::makeF0( goldN, goldK );
    Material *gold = new Material( Number( 0 ), Number( 0 ), goldF0, Color( 0, 0, 0 ), Color( 0, 0, 0 ), REFLECTIVE );


    Color glassN = Color( 1.5f, 1.5f, 1.5f );
    Color glassK = Color( 0.0f, 0.0f, 0.0f );
    Color glassF0 = Material::makeF0( glassN, glassK );
    Material *glass = new Material( Number( 1.5f ), Number( 0 ), glassF0, Color( 0, 0, 0 ), Color( 0, 0, 0 ), REFRACTIVE );

    InfiniteCylinder *glassCylinder = new InfiniteCylinder( glass, Number( 3 ));
    glassCylinder->setRotateZ( Number( M_PI / 6 ));
    addObject( glassCylinder );

    InfiniteCylinder *texturedCylinder = new InfiniteCylinder( cylinderMaterial, Number( 3 ));
    texturedCylinder->setRotateX( Number(( M_PI / 6 ) * 5 ));
    texturedCylinder->setRotateY( Number(( M_PI / 6 ) * 4 ));
    texturedCylinder->setShift( Vector( -10, 0, 2 ));
    addObject( texturedCylinder );

    InfiniteCylinder *roomCylinder = new InfiniteCylinder( gold, Number( 30 ));
    addObject( roomCylinder );
}

void Scene::smoothOutEdges() {
    for( int xPos = 1; xPos < screenWidth - 1; xPos++ ){
        for( int yPos = 1; yPos < screenHeight - 1; yPos++ ){
            if( needSmoothing( xPos, yPos ))
                image[yPos * screenWidth + xPos] = getSmoothedColor( xPos, yPos );
        }
    }
}


bool Scene::needSmoothing( int xPos, int yPos ) {
    Color c1 = image[yPos * screenWidth + xPos];
    Color c2 = image[( yPos + 1 ) * screenWidth + xPos];
    Color c3 = image[yPos * screenWidth + xPos + 1];
    Color c4 = image[( yPos + 1 ) * screenWidth + xPos + 1];

    Color sum = c1 + c2 + c3 + c4;
    Color average = sum / 4;

//    if( c1 < average / 2 || c1 > average * 2 )
//        return true;

    return false;
}

Color Scene::getSmoothedColor( int xPos, int yPos ) {
    Color sum;

    int antialiasing = 4;

    Number step( 1.0 / antialiasing );
    for( Number xSubPos = xPos - 0.5 + step / 2; xSubPos < xPos + 0.5; xSubPos += step ){
        for( Number ySubPos = yPos - 0.5 + step / 2; ySubPos < yPos + 0.5; ySubPos += step ){
            Ray ray = cam.getRay( xSubPos.value, ySubPos.value );
            Color subColor = trace( ray, 0 );
            sum = sum + subColor;
        }
    }

    return sum / ( antialiasing * antialiasing );
}
