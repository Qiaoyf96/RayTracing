//
// Created by 乔逸凡 on 2017/5/19.
//

#include "Shape.h"

float3 Shape::getN() {
    return n;
}

bool Shape::isInside() {
    return inside;
}

double Shape::getNt() {
    return nt;
}

Shape::Shape(const float3 &pos) :pos(pos) {
    nt = 1.5;
}
