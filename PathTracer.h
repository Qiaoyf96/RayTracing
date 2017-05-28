//
// Created by 乔逸凡 on 2017/5/19.
//

#ifndef RAY_TRACING_PATHTRACER_H
#define RAY_TRACING_PATHTRACER_H

#include "RayTracer.h"
#include "Shape.h"
#include "Ray.h"
#include <vector>

class PathTracer: public RayTracer {
public:
    color tracing(Ray ray, int depth, vector<Shape*> shapeList);
};

#endif //RAY_TRACING_PATHTRACER_H
