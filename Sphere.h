//
// Created by 乔逸凡 on 2017/5/28.
//

#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H

#include "Shape.h"
#include "Texture.h"
#include <cmath>

class Sphere: public Shape {
public:
    double r;
    color e;
    color c;
    Refl_t refl;

    Sphere(const float3& pos, double r, const color& e, const color& c, Refl_t refl);

    double intersect(Ray ray);
    virtual color getColor();
    color getEmission();
    Refl_t getRefl();
};

class textureSphere: public Sphere {
    Texture texture;
public:
    textureSphere(const float3& pos, double r, const color& e);
    color getColor();
};

#endif //RAY_TRACING_SPHERE_H
