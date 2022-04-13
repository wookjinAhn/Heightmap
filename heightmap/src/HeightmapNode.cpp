//
// Created by wj on 22. 4. 8..
//

#include "../include/HeightmapNode.h"

namespace camel
{
//    HeightmapNode::~HeightmapNode()
//    {
//        for (int i = 0; i < mPoints.size(); i++) {
//            delete mPoints[i];
//        }
//        mPoints.clear();
//    }

    std::vector<Point3D*> HeightmapNode::GetPoints() const
    {
        return mPoints;
    }

    void HeightmapNode::SetPoints(Point3D* point)
    {
        mPoints.push_back(point);
    }

    void HeightmapNode::MakeHeightMap(Point3D* points)
    {
        if (mMapPair.find(std::make_pair(points->GetEndNodeXY().GetX(), points->GetEndNodeXY().GetY())) == mMapPair.end())	// exist
        {
            mMapPair.insert({ std::make_pair(points->GetEndNodeXY().GetX(), points->GetEndNodeXY().GetY()), points->GetZ() });
        }
        else	// not exist
        {
            float beforeHeight = mMapPair.find(std::make_pair(points->GetEndNodeXY().GetX(), points->GetEndNodeXY().GetY()))->second;
            if (beforeHeight < points->GetZ())
            {
                mMapPair.find(std::make_pair(points->GetEndNodeXY().GetX(), points->GetEndNodeXY().GetY()))->second = points->GetZ();
            }
        }
    }

    void HeightmapNode::MakeMapToVector()
    {
        for (auto iter = mMapPair.begin(); iter != mMapPair.end(); ++iter)
        {
            Point3D* pointXYZ = new Point3D;
            pointXYZ->SetXYZ(iter->first.first, iter->first.second, iter->second);
            mPoints.push_back(pointXYZ);
        }
    }

    void HeightmapNode::WriteVectorToPCD(const std::string &outputPath)
    {
        time_t t;
        struct tm* timeinfo;
        time(&t);
        timeinfo = localtime(&t);

        std::string hour, min;

        if (timeinfo->tm_hour < 10) hour = "0" + std::to_string(timeinfo->tm_hour);
        else hour = std::to_string(timeinfo->tm_hour);

        if (timeinfo->tm_min < 10) min = "0" + std::to_string(timeinfo->tm_min);
        else min = std::to_string(timeinfo->tm_min);

        std::string filePath = outputPath + hour + min + ".pcd";

        std::ofstream fout;
        fout.open(filePath);

        fout << "VERSION" << std::endl;
        fout << "FIELDS x y z" << std::endl;
        fout << "SIZE 4 4 4" << std::endl;
        fout << "TYPE F F F" << std::endl;
        fout << "COUNT 1 1 1" << std::endl;
        fout << "WIDTH 1" << std::endl;
        fout << "HEIGHT " << mPoints.size() << std::endl;
        fout << "VIEWPOINT 0 0 0 1 0 0 0" << std::endl;
        fout << "POINTS " << mPoints.size() << std::endl;
        fout << "DATA ascii" << std::endl;

        for (int i = 0; i < mPoints.size(); i++)
        {
            fout << mPoints[i]->GetX() << " " << mPoints[i]->GetY() << " " << mPoints[i]->GetZ() << "\n";
        }

        fout.close();
    }
}