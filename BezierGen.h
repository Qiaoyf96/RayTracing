//
// Created by 乔逸凡 on 2017/5/10.
//

#ifndef RAY_TRACING_BEZIERGEN_H
#define RAY_TRACING_BEZIERGEN_H

#include "float3.h"
#include "int4.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class BezierGen {
    float3 **p;
    int m, n;
    vector<float3> points;
    vector<int4> meshes;
    double du, dv;
public:
    BezierGen(double du = 0.1, double dv = 0.1f);

    void calculate();

    float3 P(double u, double v, int i, int j, int k , int l);

    void report(string s);

    virtual ~BezierGen();
};

#endif //RAY_TRACING_BEZIERGEN_H
