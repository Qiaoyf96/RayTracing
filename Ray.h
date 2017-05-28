//
// Created by 乔逸凡 on 2017/5/19.
//

#ifndef RAY_TRACING_RAY_H
#define RAY_TRACING_RAY_H

#include "float3.h"

struct Ray {
    float3 pos, dir;

    inline Ray(const float3 &pos, const float3 &dir) : pos(pos), dir(dir) {}
};

#endif //RAY_TRACING_RAY_H
