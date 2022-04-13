//
// Created by wj on 22. 4. 8..
//

#ifndef HEIGHTMAP_BOUNDARY_H
#define HEIGHTMAP_BOUNDARY_H

#include "Point3D.h"

namespace camel
{
    class Boundary
    {
    public:
        Boundary();
        Boundary(float x, float y, float w, float h);
//        Boundary(float minX, float maxX, float y);
        Boundary(float x, float minY, float maxY);

        float GetX() const;
        float GetY() const;
        float GetW() const;
        float GetH() const;

        void SetBoundary(float const x, float const y, float const w, float const h);

        bool IsConstained(Point3D* p) const;

    private:
        float mX, mY, mW, mH;
    };
}

#endif //HEIGHTMAP_BOUNDARY_H
