//
// Created by 乔逸凡 on 2017/5/29.
//

#ifndef RAY_TRACING_PROGRESSIVEPHOTONMAPPING_H
#define RAY_TRACING_PROGRESSIVEPHOTONMAPPING_H

#include "RayTracer.h"
#include "photon.h"
#include "Box.h"

#define ALPHA 0.7

class ProgressivePhotonMapping : public RayTracer {
    vector<photon*> photonList;
    int pixel_index;
    void tracing(Ray ray, int depth, vector<Shape*> &shapeList, bool eye, color fl, color emi);
    void buildHashGrid(int height, int width);
    Box box;
    double hash_s;
    vector<photon*> *hash_grid;
    int hash_max = 10000007;

public:
    void getPicture(int height, int width, float3 cx, float3 cy, float3 pos, float3 dir, int samples, vector<Shape*> &shapeList, Film& film);
    ~ProgressivePhotonMapping();
};


#endif //RAY_TRACING_PROGRESSIVEPHOTONMAPPING_H
