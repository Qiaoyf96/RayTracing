//
// Created by 乔逸凡 on 2017/5/19.
//

#ifndef RAY_TRACING_SHAPE_H
#define RAY_TRACING_SHAPE_H

#include "Ray.h"
#include "color.h"

enum Refl_t { DIFF, SPEC, REFR };

class Shape {
public:
    float3 pos;
    float3 n;
    bool inside;
    double nt;

    virtual double intersect(Ray ray) = 0;
    virtual color getColor() = 0;
    virtual color getEmission() = 0;
    virtual Refl_t getRefl() = 0;

    Shape(const float3& pos);
    float3 getN();
    bool isInside();
    double getNt();
};


#endif //RAY_TRACING_SHAPE_H
