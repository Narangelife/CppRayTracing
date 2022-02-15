#include "Image.h"
#include "Ray.h"
#include "Camera.h"
#include "Scene.h"
#include <iostream>
#include <ctime>

int main() {
    int nx = 960;
    int ny = 540;
    int ns = 10;
    std::unique_ptr<rayTracing::Scene> scene(std::make_unique<rayTracing::Scene>(nx, ny, ns));
    scene->render();

    return 0;
}
