//
// Created by 乔逸凡 on 2017/5/29.
//

#include "Box.h"

#define MAX 1e20

void Box::fit(const float3 &p) {
    if (p.x < minp.x) minp.x = p.x;
    if (p.y < minp.y) minp.y = p.y;
    if (p.z < minp.z) minp.z = p.z;
    if (p.x > maxp.x) maxp.x = p.x;
    if (p.y > maxp.y) maxp.y = p.y;
    if (p.z > maxp.z) maxp.z = p.z;
}

void Box::init() {
    minp = float3(MAX, MAX, MAX);
    maxp = float3(-MAX, -MAX, -MAX);
}
