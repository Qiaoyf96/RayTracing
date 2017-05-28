//
// Created by 乔逸凡 on 2017/5/19.
//

#include "Film.h"

Film::Film(int width, int height) : width(width), height(height) {
    c = new color [width * height];
}

Film::~Film() {
    delete [] c;
}

