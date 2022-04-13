//
// Created by wj on 22. 4. 8..
//

#ifndef HEIGHTMAP_POINT2D_H
#define HEIGHTMAP_POINT2D_H

#include <camel-euclid/vector/Vector2D.h>

namespace camel
{
    class Point2D : public CamelVector::Vector2D
    {
    public:
        Point2D();
        Point2D(float x, float z);
    };
}

#endif //HEIGHTMAP_POINT2D_H
