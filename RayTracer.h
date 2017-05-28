//
// Created by 乔逸凡 on 2017/5/10.
//

#ifndef RAY_TRACING_RAYTRACER_H
#define RAY_TRACING_RAYTRACER_H


#include "Ray.h"
#include "Shape.h"
#include <vector>

using namespace std;

class RayTracer {
public:
    virtual color tracing(Ray ray, int depth, vector<Shape*> shapeList) = 0;
    bool intersect(Ray ray, double &t, int &id, vector<Shape*> shapeList);
};


#endif //RAY_TRACING_RAYTRACER_H
