//
// Created by wj on 22. 4. 8..
//
#include "../include/Boundary.h"

namespace quadtree
{
    Boundary::Boundary()
        : mX(0.0f)
        , mZ(0.0f)
        , mW(0.0f)
        , mH(0.0f)
    {
    }

    Boundary::Boundary(float x, float z, float w, float h)
        : mX(x)
        , mZ(z)
        , mW(w)
        , mH(h)
    {
    }

    Boundary::Boundary(float minX, float maxX, float z)
        : mX((maxX + minX) / 2)
        , mZ(z / 2)
        , mW((maxX - minX) / 2)
        , mH(z / 2)
    {
    }

    float Boundary::GetX() const
    {
        return mX;
    }

    float Boundary::GetZ() const
    {
        return mZ;
    }

    float Boundary::GetW() const
    {
        return mW;
    }

    float Boundary::GetH() const
    {
        return mH;
    }

    void Boundary::SetBoundary(const float x, const float z, const float w, const float h)
    {
        mX = x;
        mZ = z;
        mW = w;
        mH = h;
    }

    bool Boundary::IsConstained(Point3D *p) const
    {
        return (p->GetX() >= mX - mW && p->GetX() < mX + mW && p->GetZ() >= mZ - mH && p->GetZ() < mZ + mH);
    }
}