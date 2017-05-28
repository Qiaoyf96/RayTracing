//
// Created by 乔逸凡 on 2017/5/16.
//

#ifndef RAY_TRACING_CAMERA_H
#define RAY_TRACING_CAMERA_H

#include <opencv2/opencv.hpp>
#include "Scene.h"
#include "Film.h"
#include "float3.h"
#include "Sample.h"
#include "RayTracer.h"

using namespace cv;

int toInt(double x) {
    if (x > 255) x = 255;
    if (x < 0) x = 0;
    return int(pow(x / 255, (1 / 2.2)) * 255 + 0.5);
}

template <class _Sample, class _RayTracer>
class Camera: public _Sample, public _RayTracer {
    float3 pos;
    float3 dir;
    double focus = 0.5312;
    Film film;
    int samples;

    int width, height;

public:
    Camera(const float3 &pos, const float3 &dir, int width, int height, int samples);

    Mat getFilm() const;

    void getPicture(Scene* scene);
};

template <class _Sample, class _RayTracer>
Mat Camera<_Sample, _RayTracer>::getFilm() const {
    Mat mat(height, width, CV_8UC3);
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++) {
            Vec3b &bgr = mat.at<Vec3b>((height - j - 1), i);
            bgr[0] = toInt(film.c[j * width + i].b);
            bgr[1] = toInt(film.c[j * width + i].g);
            bgr[2] = toInt(film.c[j * width + i].r);
        }
    return mat;
}

template <class _Sample, class _RayTracer>
void Camera<_Sample, _RayTracer>::getPicture(Scene* scene) {
    float3 cx = float3(width * focus / height, 0, 0);
    float3 cy = cx.cross(dir).norm() * focus;
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
                        c = c + _RayTracer::tracing(Ray(pos + d * 130, d.norm()), 0, scene->shapeList) * (1.0 / samples);
                    }
                    film.c[y * width + x] = film.c[y * width + x] + c.norm() * 0.25;
                }
        }
}

template <class _Sample, class _RayTracer>
Camera<_Sample, _RayTracer>::Camera(const float3 &pos, const float3 &dir, int width, int height, int samples) : pos(pos), dir(dir), width(width),
                                                                              height(height), film(width, height), samples(samples) {}


#endif //RAY_TRACING_CAMERA_H

