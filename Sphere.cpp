//
// Created by 乔逸凡 on 2017/5/28.
//

#include "Sphere.h"

#define eps 1e-4

double Sphere::intersect(Ray ray) {
    float3 v = pos - ray.pos;
    double b = v.dot(ray.dir);
    double det = b * b - v.dot(v) + r * r;
    if (det < 0) return -1;
    else det = sqrt(det);
    double ans;
    if (b - det > eps) ans = b - det;
    else if (b + det > eps) ans = b + det;
    else ans =  -1;
    if (ans > eps) {
        n = (ray.pos + ans * ray.dir - pos).norm();
        inside = (n.dot(ray.dir) > 0);
    }
    return ans;
}

color Sphere::getColor() {
    return c;
}

color Sphere::getEmission() {
    return e;
}

Refl_t Sphere::getRefl() {
    return refl;
}

Sphere::Sphere(const float3& pos, double r, const color& e, const color& c, Refl_t refl) :Shape(pos), r(r), e(e), c(c), refl(refl){}

textureSphere::textureSphere(const float3 &pos, double r, const color &e) : Sphere(pos, r, e, color(), DIFF) {}

double norm(double x) {
    if (x > 1) return 1;
    if (x < -1) return -1;
    return x;
}

color textureSphere::getColor() {
    double a = acos(norm(-n.dot(float3(0, 0, 1))));
    double b = sin(a) == 0 ? 1 : acos(norm(min(max(n.dot(float3(0, 1, 0)) / sin(a), -1.0), 1.0)));
    double u = a / M_PI, v = b / 2 / M_PI;
    if (n.dot(float3(1, 0, 0)) < 0) v = 1 - v;
    return texture.getColor(u, v);
}
