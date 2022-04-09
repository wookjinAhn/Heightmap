//
// Created by wj on 22. 4. 8..
//

#include "../include/Point2D.h"

namespace camel
{
    Point2D::Point2D()
        : mX(0)
        , mZ(0)
    {
    }

    Point2D::Point2D(float x, float z)
        : mX(x)
        , mZ(z)
    {
    }

    float Point2D::GetX() const
    {
        return mX;
    }

    float Point2D::GetZ() const
    {
        return mZ;
    }

    void Point2D::SetX(const float x)
    {
        mX = x;
    }

    void Point2D::SetZ(const float z)
    {
        mZ = z;
    }

}