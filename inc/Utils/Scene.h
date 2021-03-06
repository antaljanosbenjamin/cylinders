#pragma once

#include <memory>
#include <mutex>
#include <random>
#include "CameraUtils/Camera.h"
#include "Lights/AmbientLight.h"
#include "Materials/Material.h"
#include "Materials/TableMaterial.h"
#include "Objects/InfiniteCylinder.h"
#include "Objects/Object.h"
#include "Objects/Plane.h"

class Scene {
  protected:
    Camera cam;

    AmbientLight ambientLight;
    Color *image;
    const int screenWidth;
    const int screenHeight;

    std::mutex mutex;
    int nextPixelNumber;

    static int TRACE_DEPTH;

  public:
    Scene(Camera cam_init, int screenW, int screenH, Color *img);

    ~Scene();

    std::vector<std::shared_ptr<Light>> lights;

    std::vector<std::shared_ptr<Object>> objects;

    void addObject(std::shared_ptr<Object> object);

    void addLight(std::shared_ptr<Light> light);

    void render();

    RayHit intersectAll(Ray &r);

    Color trace(Ray &r, int d);

    void build();

  private:
    void smoothOutEdges();

    bool needSmoothing(int xPos, int yPos);

    Color getSmoothedColor(int xPos, int yPos);

    static void renderTask(Scene *scene);

    static void smoothTask(Scene *scene, Color *targetImage);
};
