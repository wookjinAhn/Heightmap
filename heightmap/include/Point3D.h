//
// Created by wj on 22. 4. 8..
//

#ifndef HEIGHTMAP_POINT3D_H
#define HEIGHTMAP_POINT3D_H

#include <camel-euclid/vector/Vector3D.h>
#include "Point2D.h"

namespace camel
{
    class Point3D : public CamelVector::Vector3D
    {
    public:
        Point3D();
        Point3D(float x, float y, float z);

        Point2D GetEndNodeXY() const;

        void SetEndNodeXY(Point2D const endNodeXY);
        void SetEndNodeXY(float const x, float const y);

    private:
        Point2D mEndNodeXY;
    };
}
#endif //HEIGHTMAP_POINT3D_H
