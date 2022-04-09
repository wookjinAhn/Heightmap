//
// Created by wj on 22. 4. 8..
//

#include "../include/Point3D.h"

namespace camel
{
    Point3D::Point3D()
        : mX(0.0f)
        , mY(0.0f)
        , mZ(0.0f)
    {
    }

    Point3D::Point3D(float x, float y, float z)
        : mX(x)
        , mY(y)
        , mZ(z)
    {
    }

    float Point3D::GetX() const
    {
        return mX;
    }

    float Point3D::GetY() const
    {
        return mY;
    }

    float Point3D::GetZ() const
    {
        return mZ;
    }

    Point2D Point3D::GetEndNodeXZ() const
    {
        return mEndNodeXZ;
    }

    void Point3D::SetX(float const x)
    {
        mX = x;
    }

    void Point3D::SetY(float const y)
    {
        mY = y;
    }

    void Point3D::SetZ(float const z)
    {
        mZ = z;
    }

    void Point3D::SetXYZ(float const x, float const y, float z)
    {
        mX = x;
        mY = y;
        mZ = z;
    }

    void Point3D::SetEndNodeXZ(const Point2D endNodeXZ)
    {
        mEndNodeXZ = endNodeXZ;
    }

    void Point3D::SetEndNodeXZ(const float x, const float z)
    {
        mEndNodeXZ.SetX(x);
        mEndNodeXZ.SetZ(z);
    }
}