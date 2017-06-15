//
// Created by 乔逸凡 on 2017/5/29.
//

#ifndef RAY_TRACING_PHOTON_H
#define RAY_TRACING_PHOTON_H

#include "float3.h"
#include "color.h"

class photon {
public:
    float3 pos, n;
    color col, flux;
    int pixIndex;
    double r2;
    int times = 0;
};


#endif //RAY_TRACING_PHOTON_H
