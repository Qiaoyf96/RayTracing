//
// Created by 乔逸凡 on 2017/5/6.
//

#include "float3.h"

#include <cmath>

float3::float3(double x, double y, double z) : x(x), y(y), z(z) {}

float3::float3() {
    x = 0;
    y = 0;
    z = 0;
}

float3& float3::operator=(const float3 &b) {
    x = b.x;
    y = b.y;
    z = b.z;
    return *this;
}

float3 float3::operator+(const float3 &b) const {
    return float3(x + b.x, y + b.y, z + b.z);
}

float3 float3::operator*(double r) const {
    return float3(r * x, r * y, r * z);
}

bool float3::operator==(const float3 &rhs) const {
    return x == rhs.x &&
           y == rhs.y &&
           z == rhs.z;
}

bool float3::operator!=(const float3 &rhs) const {
    return !(rhs == *this);
}

float3 float3::operator-(const float3 &b) const {
    return float3(x - b.x, y - b.y, z - b.z);
}

double float3::dot(const float3 &b) const {
    return x * b.x + y * b.y + z * b.z;
}

float3 float3::norm() const {
    double len = sqrtf(this->dot(*this));
    return *this * (1 / len);
}

float3 float3::cross(const float3 &b) const {
    return float3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
}

float3 float3::operator-(double a) const {
    return float3(x - a, y - a, z - a);
}

float3 float3::operator+(double a) const {
    return float3(x + a, y + a, z + a);
}

float3 operator*(double r, const float3 &a) {
    return a * r;
}
