//
// Created by 乔逸凡 on 2017/5/10.
//

#include "RayTracer.h"

#define INF 1e30

bool RayTracer::intersect(Ray ray, double &t, int &id, vector<Shape*> shapeList) {
    double d;
    t = INF;
    int i = 0;
    for (Shape* obj: shapeList) {
        d = obj->intersect(ray);
        if (d > 0 && d < t) {
            t = d;
            id = i;
        }
        i++;
    }
    return t < INF;
}

