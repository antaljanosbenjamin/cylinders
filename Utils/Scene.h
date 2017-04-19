//
// Created by kovi on 4/16/17.
//

#ifndef CYLINDERS_SCENE_H
#define CYLINDERS_SCENE_H

#include <random>
#include <mutex>


#include "../CameraUtils/Camera.h"
#include "../Lights/AmbientLight.h"
#include "../Objects/Object.h"
#include "../Materials/Material.h"
#include "../Objects/Plane.h"
#include "../Materials/TableMaterial.h"
#include "../Objects/InfiniteCylinder.h"

class Scene {
protected:
    Camera cam;

    AmbientLight ambientLight;
    Color *image;
    int screenWidth;
    int screenHeight;

    std::mutex mutex;
    int nextPixelNumber;

    static int TRACE_DEPTH;

public:
    Scene( Camera cam_init, int screenW, int screenH, Color *img );

    ~Scene();

    int lightsNum;
    Light *lights[3];

    int objectsNum;
    Object *objects[100];

    void addObject( Object *obj );

    void addLight( Light *light );

    void render();

    RayHit intersectAll( Ray &r );

    Color trace( Ray &r, int d );

    void build();

private:

    void smoothOutEdges();

    bool  needSmoothing( int xPos, int yPos );

    Color getSmoothedColor( int xPos, int yPos );

    static void renderTask( Scene* scene);

};

#endif //CYLINDERS_SCENE_H
