//
// Created by 乔逸凡 on 2017/5/19.
//

#ifndef RAY_TRACING_FILM_H
#define RAY_TRACING_FILM_H

#include "color.h"

class Film {
    int width, height;
public:
    color * c;
    Film(int width, int height);

    virtual ~Film();
};


#endif //RAY_TRACING_FILM_H
