//
// Created by 乔逸凡 on 2017/5/16.
//

#ifndef RAY_TRACING_CAMERA_H
#define RAY_TRACING_CAMERA_H

#include <opencv2/opencv.hpp>
#include "Scene.h"
#include "Film.h"
#include "float3.h"
#include "RayTracer.h"

using namespace cv;

int toInt(double x) {
    if (x > 255) x = 255;
    if (x < 0) x = 0;
    return int(pow(x / 255, (1 / 2.2)) * 255 + 0.5);
}

template <class _RayTracer>
class Camera: public _RayTracer {
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

template <class _RayTracer>
Mat Camera<_RayTracer>::getFilm() const {
    Mat mat(height, width, CV_8UC3);
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++) {
            Vec3b &bgr = mat.at<Vec3b>(j, i);
            bgr[0] = toInt(film.c[j * width + i].b);
            bgr[1] = toInt(film.c[j * width + i].g);
            bgr[2] = toInt(film.c[j * width + i].r);
        }
    return mat;
}

template <class _RayTracer>
void Camera<_RayTracer>::getPicture(Scene* scene) {
    float3 cx = float3(width * focus / height, 0, 0);
    float3 cy = cx.cross(dir).norm() * focus;
    _RayTracer::getPicture(height, width, cx, cy, pos, dir, samples, scene->shapeList, film);
}

template <class _RayTracer>
Camera<_RayTracer>::Camera(const float3 &pos, const float3 &dir, int width, int height, int samples) : pos(pos), dir(dir), width(width),
                                                                              height(height), film(width, height), samples(samples) {}


#endif //RAY_TRACING_CAMERA_H

