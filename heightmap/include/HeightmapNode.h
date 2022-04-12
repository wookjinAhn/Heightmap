//
// Created by wj on 22. 4. 8..
//

#ifndef HEIGHTMAP_HEIGHTMAPNODE_H
#define HEIGHTMAP_HEIGHTMAPNODE_H

#include <vector>
#include <map>
#include <fstream>

#include "Point3D.h"
//#include <camel-euclid/vector/Point3D.h>

namespace camel
{
    class HeightmapNode
    {
    public:
        ~HeightmapNode();

        std::vector<CamelVector::Point3D*> GetPoints() const;

        void MakeHeightMap(Point3D* points);
        void MakeMapToVector();

        void WriteVectorToPCD(const std::string &outputPath);

    private:
        std::map<std::pair<float, float>, float> mMapPair;
        std::vector<CamelVector::Point3D*> mPoints;
    };
}

#endif //HEIGHTMAP_HEIGHTMAPNODE_H
