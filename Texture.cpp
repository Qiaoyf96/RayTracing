//
// Created by 乔逸凡 on 2017/5/28.
//

#include "Texture.h"

Texture::Texture(char *s) {
    m = imread(s);
}

color Texture::getColor(double x, double y) {
    Vec3b c = m.at<Vec3b>(int(x * m.rows), int(y * m.cols));
    return color(c[2], c[1], c[0]);
}
