#include "header.h"

int main() {
    Camera<ProgressivePhotonMapping> c(float3(50,52,295.6), float3(0,-0.042612,-1).norm(), 1024, 768, 3000);
    Scene scene;
    textureSphere sphere1(float3(27,10,100), 10, color());
    Sphere sphere2(float3(73,16.5,78), 16.5, color(), color(200, 200, 200), REFR);
    Sphere sphere3(float3(27,16.5,37), 16.5, color(), color(200, 200, 200), SPEC);
    //Sphere light(float3(50,681.6-.27,81.6), 600, color(6060, 6060, 6060), color(), DIFF);
    Sphere left(float3(1e5+1,40.8,81.6), 1e5, color(), color(200, 100, 100),DIFF);
    Sphere right(float3(-1e5+99,40.8,81.6), 1e5, color(), color(100, 100, 200),DIFF);
    Sphere back(float3(50,40.8, 1e5), 1e5, color(), color(200, 200, 200),DIFF);
    Sphere front(float3(50,40.8,-1e5+170), 1e5, color(), color(), DIFF);
    Sphere bot(float3(50, 1e5, 81.6), 1e5, color(), color(200, 200, 200), DIFF);
    //textureSphere bot(float3(50, 1e5, 81.6), 1e5, color());
    Sphere top(float3(50,-1e5+81.6,81.6), 1e5, color(), color(200, 200, 200), DIFF);
    scene.addObj(&sphere1);
    scene.addObj(&sphere2);
    scene.addObj(&sphere3);
    //scene.addObj(&light);
    scene.addObj(&left);
    scene.addObj(&right);
    scene.addObj(&back);
    scene.addObj(&front);
    scene.addObj(&bot);
    scene.addObj(&top);
    c.getPicture(&scene);
    Mat a = c.getFilm();
    imwrite("../test.png", a);
    return 0;
}