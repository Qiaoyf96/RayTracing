//
// Created by 乔逸凡 on 2017/5/10.
//

#ifndef RAY_TRACING_RAYTRACER_H
#define RAY_TRACING_RAYTRACER_H


#include "Ray.h"
#include "Shape.h"
#include "Film.h"
#include <vector>

using namespace std;

class RayTracer {
public:
    bool intersect(Ray ray, double &t, int &id, vector<Shape*> &shapeList);
    virtual void getPicture(int height, int width, float3 cx, float3 cy, float3 pos, float3 dir, int samples, vector<Shape*> &shapeList, Film& film) = 0;
};


#endif //RAY_TRACING_RAYTRACER_H
