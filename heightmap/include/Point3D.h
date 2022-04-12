//
// Created by wj on 22. 4. 8..
//

#ifndef HEIGHTMAP_POINT3D_H
#define HEIGHTMAP_POINT3D_H

#include "../include/Point2D.h"
//#include <camel-euclid/vector/Point2D.h>

namespace camel
{
    class Point3D
    {
    public:
        Point3D();
        Point3D(float x, float y, float z);

        float GetX() const;
        float GetY() const;
        float GetZ() const;
        Point2D GetEndNodeXZ() const;

        void SetX(float const x);
        void SetY(float const y);
        void SetZ(float const z);
        void SetXYZ(float const x, float const y, float const z) ;
        void SetEndNodeXZ(Point2D const endNodeXZ);
        void SetEndNodeXZ(float const x, float const z);

    private:
        float mX, mY, mZ;
        Point2D mEndNodeXZ;
    };
}
#endif //HEIGHTMAP_POINT3D_H
