//
// Created by wj on 22. 4. 8..
//

#include "../include/Heightmap.h"

namespace quadtree
{
    Heightmap::~Heightmap()
    {
        for (int i = 0; i < mPoints.size(); i++) {
            delete mPoints[i];
        }
        mPoints.clear();
    }

    std::vector<Point3D*> Heightmap::GetPoints() const
    {
        return mPoints;
    }

    void Heightmap::MakeHeightMap(Point3D *points)
    {
        if (mMapPair.find(std::make_pair(points->GetEndNodeXZ().GetX(), points->GetEndNodeXZ().GetZ())) == mMapPair.end())	// exist
        {
            mMapPair.insert({ std::make_pair(points->GetEndNodeXZ().GetX(), points->GetEndNodeXZ().GetZ()), points->GetY() });
        }
        else	// not exist
        {
            float beforeHeight = mMapPair.find(std::make_pair(points->GetEndNodeXZ().GetX(), points->GetEndNodeXZ().GetZ()))->second;
            if (beforeHeight > points->GetY())
            {
                mMapPair.find(std::make_pair(points->GetEndNodeXZ().GetX(), points->GetEndNodeXZ().GetZ()))->second = points->GetY();
            }
        }
    }

    void Heightmap::MakeMapToVector()
    {
        for (auto iter = mMapPair.begin(); iter != mMapPair.end(); ++iter)
        {
            Point3D* pointXYZ = new Point3D;
            pointXYZ->SetXYZ(iter->first.first, iter->second, iter->first.second);
            mPoints.push_back(pointXYZ);
        }
    }
}