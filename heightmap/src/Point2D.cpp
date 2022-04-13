//
// Created by wj on 22. 4. 8..
//

#include "../include/Point2D.h"

namespace camel
{
    Point2D::Point2D()
        : CamelVector::Vector2D()
    {
    }

    Point2D::Point2D(float x, float y)
        : CamelVector::Vector2D(x, y)
    {
    }
}