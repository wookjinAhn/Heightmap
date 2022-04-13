//
// Created by wj on 22. 4. 8..
//

#include "../include/Point3D.h"

namespace camel
{
    Point3D::Point3D()
        : CamelVector::Vector3D()
    {
    }

    Point3D::Point3D(float x, float y, float z)
        : CamelVector::Vector3D(x, y, z)
    {
    }

    Point2D Point3D::GetEndNodeXY() const
    {
        return mEndNodeXY;
    }

    void Point3D::SetEndNodeXY(const Point2D endNodeXY)
    {
        mEndNodeXY = endNodeXY;
    }

    void Point3D::SetEndNodeXY(const float x, const float y)
    {
        mEndNodeXY.SetX(x);
        mEndNodeXY.SetY(y);
    }
}