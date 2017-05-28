//
// Created by 乔逸凡 on 2017/5/19.
//

#ifndef RAY_TRACING_SCENE_H
#define RAY_TRACING_SCENE_H

#include "Shape.h"
#include <vector>

using namespace std;

class Scene {
public:
    vector<Shape*> shapeList;
    void addObj(Shape* a);
};


#endif //RAY_TRACING_SCENE_H
