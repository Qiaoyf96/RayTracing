//
// Created by 乔逸凡 on 2017/5/29.
//

#ifndef RAY_TRACING_BOX_H
#define RAY_TRACING_BOX_H

#include "float3.h"

class Box {
public:
    float3 minp, maxp;
    void fit(const float3& p);
    void init();
};


#endif //RAY_TRACING_BOX_H
