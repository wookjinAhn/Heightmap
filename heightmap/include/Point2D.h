//
// Created by wj on 22. 4. 8..
//

#ifndef HEIGHTMAP_POINT2D_H
#define HEIGHTMAP_POINT2D_H

//#include <camel-euclid/vector/Point2D.h>

namespace camel
{
    class Point2D
    {
    public:
        Point2D();
        Point2D(float x, float z);

        float GetX() const;
        float GetZ() const;

        void SetX(const float x);
        void SetZ(const float z);

    private:
        float mX, mZ;
    };
}

#endif //HEIGHTMAP_POINT2D_H
