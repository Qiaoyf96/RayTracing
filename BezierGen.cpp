//
// Created by 乔逸凡 on 2017/5/10.
//

#include "BezierGen.h"

BezierGen::BezierGen(double du, double dv) : du(du), dv(dv) {
    cin >> m >> n;
    p = new float3* [m];
    for (int i = 0; i < m; i++)
        p[i] = new float3 [n];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            double x, y, z;
            cin >> x >> y >> z;
            p[i][j] = float3(x, y, z);
        }
}

void BezierGen::calculate() {
    int nu = 1 / du + 1, nv = 1 / dv + 1;

    int pid = 0;
    for (double u = 0.0, i = 0; u <= 1.0; u += du, i++) {
        for (double v = 0.0, j = 0; v <= 1.0; v += dv, j++) {
            points.push_back(P(u, v, 0, 0, m - 1, n - 1));
            pid++;
            if (i != 0 && j != 0) {
                meshes.push_back(int4(pid - nv - 1, pid - nv, pid, pid - 1));
            }
        }
    }
}

float3 BezierGen::P(double u, double v, int i, int j, int k , int l) {
    if (k == 0 && l == 0) return p[i][j];
    if (l == 0) {
        return (1 - u) * P(u, v, i, j, k - 1, 0) + u * P(u, v, i + 1, j, k - 1, 0);
    }
    return (1 - v) * P(u, v, 0, j, k, l - 1) + v * P(u, v, 0, j + 1, k, l - 1);
}

void BezierGen::report(string s) {
    ofstream fp(s);
    for (auto point : points) {
        fp << "v " << point.x << ' ' << point.y << ' ' << point.z << endl;
    }
    for (auto mesh : meshes) {
        fp << "f";
        for (int i = 0; i < 4; i++)
            fp << ' ' << mesh.point[i];
        fp << endl;
    }
}

BezierGen::~BezierGen() {
    delete [] p;
}
