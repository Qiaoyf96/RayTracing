//
// Created by 乔逸凡 on 2017/5/6.
//

#ifndef RAY_TRACING_FLOAT3_H
#define RAY_TRACING_FLOAT3_H

class float3 {
public:
    double x, y, z;

    float3();

    float3(double x, double y, double z);

    float3& operator = (const float3 &b);

    float3 operator + (const float3 & b) const;

    float3 operator + (double a) const;

    float3 operator - (const float3 & b) const;

    float3 operator - (double a) const;

    float3 operator * (double r) const;

    bool operator==(const float3 &rhs) const;

    bool operator!=(const float3 &rhs) const;

    double dot(const float3 &b) const;

    float3 norm() const;

    float3 cross(const float3 &b) const;
};

float3 operator * (double r, const float3& a);


#endif //RAY_TRACING_FLOAT3_H
