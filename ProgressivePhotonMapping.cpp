//
// Created by 乔逸凡 on 2017/5/29.
//

#include "ProgressivePhotonMapping.h"
#include <cmath>
#include <cstdlib>

inline int hashv(long long x, long long y, long long z, long long sz) {
    return int(((x * 3856093) + (y * 9349663) + (z * 3492791)) % sz);
}

inline Ray genRay() {
    double p = 2 * M_PI * rand() / (double)RAND_MAX;
    double x = rand() / (double)RAND_MAX;
    double t = 2 * acos(sqrt(1 - x));
    double st = sin(t);
    return Ray(float3(50, 60, 85), float3(cos(p) * st, cos(t), sin(p) * st));
}

void ProgressivePhotonMapping::getPicture(int height, int width, float3 cx, float3 cy, float3 pos, float3 dir, int samples,
                                     vector<Shape *> &shapeList, Film &film) {
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++) {
            pixel_index = y * width + x;
            printf("Process %5.2lf%%\n", (y * width + x) * 100 / double(height * width));
            float3 d = cx * ((x + 0.5) / width - 0.5) + cy * (-(y + 0.5) / height + 0.5) + dir;
            tracing(Ray(pos + d * 130, d.norm()), 0, shapeList, 1, color(), color(COLORMAX, COLORMAX, COLORMAX));
        }
    printf("eye ray finished!\n");

    buildHashGrid(height, width);
    printf("build grid finished!\n");

#pragma omp parallel for schedule(dynamic, 1)
    for (int i = 0; i < samples; i++) {
        printf("%d\n", i);
        color f = color(2500, 2500, 2500) * (M_PI * 4) * COLORMAX;
        for (int j = 0; j < 1000; j++) {
            Ray r = genRay();
            tracing(r, 0, shapeList, 0, f, color(COLORMAX, COLORMAX, COLORMAX));
        }
    }

    for (photon* p : photonList) {
        film.c[p->pixIndex] = film.c[p->pixIndex] + p->flux * (1 / (M_PI * p->r2 * samples * 1000));
    }
}

void ProgressivePhotonMapping::tracing(Ray ray, int depth, vector<Shape*> &shapeList, bool eye, color fl, color emi) {
    double t;
    int id;
    depth++;
    if (!intersect(ray, t, id, shapeList) || depth >= 20) return;
    float3 pos = ray.pos + ray.dir * t;
    Shape *obj = shapeList[id];
    float3 n = obj->getN();
    bool inside = obj->isInside();
    float3 nl = inside == 1 ? n * (-1) : n;
    color col = obj->getColor();
    double maxC = col.maxColor();

    Refl_t refl = obj->getRefl();

    if (refl == DIFF) {
        double r1 = 2 * M_PI * rand() / (double)RAND_MAX, r2 = rand() / (double)RAND_MAX, r2s = sqrt(r2);
        float3 w = nl;
        float3 u = (fabs(w.x) > 0.1 ? float3(0, 1, 0) : float3(1, 0, 0)).cross(w).norm();
        float3 v = w.cross(u);
        float3 d = (u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrt(1 - r2)).norm();
        if (eye) {
            photon* p = new photon;
            p->col = col.merge(emi);
            p->pos = pos;
            p->n = n;
            p->pixIndex = pixel_index;
            photonList.push_back(p);
        }
        else {
            float3 hh = (pos - box.minp) * hash_s;
            int ix = abs(int(hh.x)), iy = abs(int(hh.y)), iz = abs(int(hh.z));
            int val = hashv(ix, iy, iz, hash_max);
            vector<photon*> &local = hash_grid[val];
            if (!local.empty()) {
                for (photon *p : local) {
                    float3 d = p->pos - pos;
                    if ((p->n.dot(n) > 1e-4) && (d.dot(d) <= p->r2)) {
                        double g = (p->times * ALPHA + ALPHA) / (p->times * ALPHA + 1);
                        p->times++;
                        p->r2 *= g;
                        p->flux = (p->flux + p->col.merge(fl) * (1 / M_PI)) * g;
                    }
                }
            }
            if (rand() / (double)RAND_MAX * COLORMAX < maxC) {
                tracing(Ray(pos, d), depth, shapeList, eye, col.merge(fl) * (COLORMAX / maxC), emi);
            }
        }
        return;
    }
    else if (refl == SPEC) {
        tracing(Ray(pos, ray.dir - n * 2 * n.dot(ray.dir)), depth, shapeList, eye, col.merge(fl), col.merge(emi));
        return;
    }
    Ray reflRay = Ray(pos, ray.dir - 2 * n * n.dot(ray.dir));
    double nt = obj->getNt(), nc = 1;
    double nnt = inside ? (nt / nc) : (nc / nt);
    double ddn = ray.dir.dot(nl);
    double cos2t = 1 - nnt * nnt * (1 - ddn * ddn);
    if (cos2t < 0) {
        tracing(reflRay, depth, shapeList, eye, fl, emi);
        return;
    }
    float3 tdir = (ray.dir * nnt - nl * (ddn * nnt + sqrt(cos2t))).norm();
    double a = nt - nc, b = nt + nc;
    double r0 = a * a / b / b;
    double c = 1 - (inside ? tdir.dot(n) : -ddn);
    double re = r0 + (1 - r0) * c * c * c * c * c;
    double tr = 1 - re, p = 0.25 + 0.5 * re, rp = re / p, tp = tr / (1 - p);
    if (eye) {
        tracing(reflRay, depth, shapeList, eye, fl, col.merge(emi) * re);
        tracing(Ray(pos, tdir), depth, shapeList, eye, fl, col.merge(emi) * tr);
    }
    else {
        if (rand() / (double)RAND_MAX < p) {
            tracing(reflRay, depth, shapeList, eye, fl, col.merge(emi));
        }
        else {
            tracing(Ray(pos, tdir), depth, shapeList, eye, fl, col.merge(emi));
        }
    }
}

ProgressivePhotonMapping::~ProgressivePhotonMapping() {
    for (photon* p : photonList) {
        delete p;
    }
}

void ProgressivePhotonMapping::buildHashGrid(int height, int width) {
    box.init();
    for (photon* p : photonList) {
        box.fit(p->pos);
    }

    float3 size = box.maxp - box.minp;
    double irad = (size.x + size.y + size.z) / 3 / (width + height) * 4;

    box.init();
    for (photon* p : photonList) {
        p->r2 = irad * irad;
        p->times = 0;
        p->flux = color();
        box.fit(p->pos - irad);
        box.fit(p->pos + irad);
    }

    hash_s = 1 / (irad * 2);
    hash_grid = new vector<photon*> [hash_max];
    for (photon* p : photonList) {
        float3 minp = ((p->pos - irad) - box.minp) * hash_s;
        float3 maxp = ((p->pos + irad) - box.minp) * hash_s;
        for (int iz = abs(int(minp.z)); iz <= abs(int(maxp.z)); iz++)
            for (int iy = abs(int(minp.y)); iy <= abs(int(maxp.y)); iy++)
                for (int ix = abs(int(minp.x)); ix <= abs(int(maxp.x)); ix++) {
                    int h = hashv(ix, iy, iz, hash_max);
                    hash_grid[h].push_back(p);
                }
    }
}
