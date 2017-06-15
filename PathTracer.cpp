//
// Created by 乔逸凡 on 2017/5/19.
//

#include "PathTracer.h"
#include <cmath>
#include <cstdlib>

color PathTracer::tracing(Ray ray, int depth, vector<Shape*> &shapeList) {
    double t;
    int id;
    if (!intersect(ray, t, id, shapeList)) return color();
    float3 pos = ray.pos + ray.dir * t;
    Shape *obj = shapeList[id];
    float3 n = obj->getN();
    bool inside = obj->isInside();
    float3 nl = inside == 1 ? n * (-1) : n;
    color col = obj->getColor();
    double maxC = col.maxColor();
    depth++;
    color e = obj->getEmission();

    if (depth > 5) {
        if (rand() / (double)RAND_MAX * COLORMAX < maxC) {
            col = col * (COLORMAX / maxC);
        }
        else {
            return e;
        }
    }

    Refl_t refl = obj->getRefl();

    if (refl == DIFF) {
        double r1 = 2 * M_PI * rand() / (double)RAND_MAX, r2 = rand() / (double)RAND_MAX, r2s = sqrt(r2);
        float3 w = nl;
        float3 u = (fabs(w.x) > 0.1 ? float3(0, 1, 0) : float3(1, 0, 0)).cross(w).norm();
        float3 v = w.cross(u);
        float3 d = (u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrt(1 - r2)).norm();
        return e + col.merge(tracing(Ray(pos, d), depth, shapeList));
    }
    else if (refl == SPEC) {
        return e + col.merge(tracing(Ray(pos, ray.dir - 2 * n * n.dot(ray.dir)), depth, shapeList));
    }
    Ray reflRay = Ray(pos, ray.dir - 2 * n * n.dot(ray.dir));
    double nt = obj->getNt(), nc = 1;
    double nnt = inside ? (nt / nc) : (nc / nt);
    double ddn = ray.dir.dot(nl);
    double cos2t = 1 - nnt * nnt * (1 - ddn * ddn);
    if (cos2t < 0) {
        return e + col.merge(tracing(reflRay, depth, shapeList));
    }
    float3 tdir = (ray.dir * nnt - nl * (ddn * nnt + sqrt(cos2t))).norm();
    double a = nt - nc, b = nt + nc;
    double r0 = a * a / b / b;
    double c = 1 - (inside ? tdir.dot(n) : -ddn);
    double re = r0 + (1 - r0) * c * c * c * c * c;
    double tr = 1 - re, p = 0.25 + 0.5 * re, rp = re / p, tp = tr / (1 - p);
    if (depth > 2) {
        if (rand() / (double)RAND_MAX < p) {
            return e + col.merge(tracing(reflRay, depth, shapeList) * rp);
        }
        return e + col.merge(tracing(Ray(pos, tdir), depth, shapeList) * tp);
    }
    return e + col.merge(tracing(reflRay, depth, shapeList) * re + tracing(Ray(pos, tdir), depth, shapeList) * tr);
}

void
PathTracer::getPicture(int height, int width, float3 cx, float3 cy, float3 pos, float3 dir, int samples, vector<Shape *> &shapeList, Film &film) {
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++) {
            printf("\rProcess %5.2lf%%", (y * width + x) * 100 / double(height * width));
            for (int sy = 0; sy < 2; sy++)
                for (int sx = 0; sx < 2; sx++) {
                    color c = color();
                    for (int s = 0; s < samples; s++) {
                        double r1 = 2 * rand() / (double) RAND_MAX;
                        double dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
                        double r2 = 2 * rand() / (double) RAND_MAX;
                        double dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);
                        float3 d = cx * (((sx + 0.5 + dx) / 2 + x) / width - 0.5) +
                                   cy * (((sy + 0.5 + dy) / 2 + y) / height - 0.5) + dir;
                        c = c + tracing(Ray(pos + d * 130, d.norm()), 0, shapeList) * (1.0 / samples);
                    }
                    film.c[(height - y - 1) * width + x] = film.c[(height - y - 1) * width + x] + c.norm() * 0.25;
                }
        }
}
