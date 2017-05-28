//
// Created by 乔逸凡 on 2017/5/28.
//

#ifndef RAY_TRACING_TEXTURE_H
#define RAY_TRACING_TEXTURE_H

#include <opencv2/opencv.hpp>
#include "color.h"

using namespace cv;

class Texture {
    Mat m;
public:
    Texture(char* s = "../texture.jpg");
    color getColor(double x, double y);
};


#endif //RAY_TRACING_TEXTURE_H
