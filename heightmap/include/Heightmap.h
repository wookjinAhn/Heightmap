//
// Created by wj on 22. 4. 8..
//

#ifndef HEIGHTMAP_HEIGHTMAP_H
#define HEIGHTMAP_HEIGHTMAP_H

#include <vector>
#include <map>

#include "Point3D.h"

namespace quadtree
{
    class Heightmap
    {
    public:
        ~Heightmap();

        std::vector<Point3D*> GetPoints() const;

        void MakeHeightMap(Point3D* points);
        void MakeMapToVector();

    private:
        std::map<std::pair<float, float>, float> mMapPair;
        std::vector<Point3D*> mPoints;
    };
}

#endif //HEIGHTMAP_HEIGHTMAP_H
