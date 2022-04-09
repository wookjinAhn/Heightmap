//
// Created by wj on 22. 4. 8..
//

#include "../include/QuadtreeNode.h"

namespace camel
{
    QuadtreeNode::QuadtreeNode(Boundary boundary, int depth, int capacity)
            : mBoundary(boundary)
            , mDepth(depth)
            , mCapacity(capacity)
    {
        mCapacityPoints.reserve(mCapacity);
    }

    QuadtreeNode::QuadtreeNode(Boundary boundary, int depth)
            : mBoundary(boundary)
            , mDepth(depth)
    {
        mCapacity = 1;
        mCapacityPoints.reserve(mCapacity);
    }

    QuadtreeNode::QuadtreeNode(HeightmapNode* heightmap, Boundary boundary, int depth, int capacity)
            : mHeightmap(heightmap)
            , mBoundary(boundary)
            , mDepth(depth)
            , mCapacity(capacity)
    {
        mCapacityPoints.reserve(mCapacity);
    }

    QuadtreeNode::QuadtreeNode(HeightmapNode* heightmap, Boundary boundary, int depth)
            : mHeightmap(heightmap)
            , mBoundary(boundary)
            , mDepth(depth)
    {
        mCapacity = 1;
    }

    QuadtreeNode::~QuadtreeNode()
    {
        for (int i = 0; i < mPoints.size(); i++) {
            delete mPoints[i];
        }
        mPoints.clear();

//        delete mHeightmap;
//        mHeightmap = nullptr;
    }

    Boundary QuadtreeNode::GetBoundary() const
    {
        return mBoundary;
    }

    void QuadtreeNode::SetBoundary(Boundary const boundary)
    {
        mBoundary = boundary;
    }

    void QuadtreeNode::SetBoundary(float const x, float const z, float const w, float const h)
    {
        mBoundary.SetBoundary(x, z, w, h);
    }

    void QuadtreeNode::SetDepth(int const depth)
    {
        mDepth = depth;
    }

    void QuadtreeNode::SetCapacity(int const capacity)
    {
        mCapacity = capacity;
    }

    void QuadtreeNode::SetHeightmap(camel::HeightmapNode* const heightmap)
    {
        std::cout << heightmap << std::endl;
        if (!mHeightmap)
        {
            mHeightmap = heightmap;
        }
        else
        {
            delete mHeightmap;
            mHeightmap = heightmap;
        }
    }

    void QuadtreeNode::InsertPoints(std::vector<Point3D*> points)
    {
        for (int i = 0; i < points.size(); i++)
        {
            int depth = 0;
//            insertNode(points[i], mHeightmap, depth);
            insertNode(points[i], mHeightmap, depth);
        }

//        mHeightmap->MakeMapToVector();
    }

    std::vector<Point3D*> QuadtreeNode::SamplingPoints(std::vector<Point3D*> inputPoints, int samplingNum)
    {
        std::vector<Point3D*> samplingPoints;
        samplingPoints.reserve(samplingNum);

        std::vector<int> sample(inputPoints.size());
        std::iota(sample.begin(), sample.end(), 0);
        std::shuffle(sample.begin(), sample.end(), std::mt19937{std::random_device{}()});

        float degree = -45.0f;
        float rotationMatrix[3][3] = { {1.0f, 0.0f, 0.0f},
                                       {0.0f, (float)std::cos(degree * D2R), (float)-std::sin(degree * D2R)},
                                       {0.0f, (float)std::sin(degree * D2R), (float)std::cos(degree * D2R)} };

        for (int i = 0; i < samplingNum; i++)
        {
            inputPoints[sample[i]]->SetXYZ(rotationMatrix[0][0] * inputPoints[sample[i]]->GetX() + rotationMatrix[0][1] * inputPoints[sample[i]]->GetY() + rotationMatrix[0][2] * inputPoints[sample[i]]->GetZ(),
                                           rotationMatrix[1][0] * inputPoints[sample[i]]->GetX() + rotationMatrix[1][1] * inputPoints[sample[i]]->GetY() + rotationMatrix[1][2] * inputPoints[sample[i]]->GetZ(),
                                           rotationMatrix[1][0] * inputPoints[sample[i]]->GetX() + rotationMatrix[2][1] * inputPoints[sample[i]]->GetY() + rotationMatrix[2][2] * inputPoints[sample[i]]->GetZ());
            samplingPoints.push_back(inputPoints[sample[i]]);
        }

        return samplingPoints;
    }

    std::vector<Point3D*> QuadtreeNode::ReadPCDToVector(const std::string& inputPath)
    {
        mPoints.reserve(307200);

        std::ifstream fin;
        fin.open(inputPath);

        std::string line;

        if (fin.is_open())
        {
            int num = 1;
            while (!fin.eof())
            {
                getline(fin, line);
                if (num > 10)
                {
                    float x, y, z;
                    std::istringstream iss(line);
                    iss >> x >> y >> z;

                    Point3D* pointXYZ = new Point3D(x, y, z);
                    mPoints.push_back(pointXYZ);
                }
                num++;
            }
        }
        fin.close();

        return mPoints;
    }

    void QuadtreeNode::WriteVectorToPCD(const std::string& outputPath)
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
        fout << "HEIGHT " << mHeightmap->GetPoints().size() << std::endl;
        fout << "VIEWPOINT 0 0 0 1 0 0 0" << std::endl;
        fout << "POINTS " << mHeightmap->GetPoints().size() << std::endl;
        fout << "DATA ascii" << std::endl;

        for (int i = 0; i < mHeightmap->GetPoints().size(); i++)
        {
            fout << mHeightmap->GetPoints()[i]->GetX() << " " << mHeightmap->GetPoints()[i]->GetY() << " " << mHeightmap->GetPoints()[i]->GetZ() << "\n";
        }

        fout.close();
    }

    void QuadtreeNode::subdivide()
    {
        float x = mBoundary.GetX();
        float z = mBoundary.GetZ();
        float w = mBoundary.GetW();
        float h = mBoundary.GetH();

        Boundary nw(x - w / 2, z + h / 2, w / 2, h / 2);
        Boundary ne(x + w / 2, z + h / 2, w / 2, h / 2);
        Boundary sw(x - w / 2, z - h / 2, w / 2, h / 2);
        Boundary se(x + w / 2, z - h / 2, w / 2, h / 2);

        mNW = std::make_unique<QuadtreeNode>(nw, mDepth, mCapacity);
        mNE = std::make_unique<QuadtreeNode>(ne, mDepth, mCapacity);
        mSW = std::make_unique<QuadtreeNode>(sw, mDepth, mCapacity);
        mSE = std::make_unique<QuadtreeNode>(se, mDepth, mCapacity);

        mbDivided = true;
    }

    void QuadtreeNode::insertNode(Point3D* point, HeightmapNode* heightmap, int depth)
    {
        mCapacityPoints.push_back(point);

        if (mDepth == depth)
        {
            heightmap->MakeHeightMap(point);
            return;
        }

        if (mCapacity < mCapacityPoints.size() && mDepth > depth)
        {
            subdivide();
        }

        if (mbDivided)
        {
            while (!mCapacityPoints.empty())
            {
                Point3D* qPoint = mCapacityPoints.back();

                mCapacityPoints.pop_back();
                if (mNW->mBoundary.IsConstained(qPoint))
                {
                    qPoint->SetEndNodeXZ(mNW->GetBoundary().GetX(), mNW->GetBoundary().GetZ());
                    mNW->insertNode(qPoint, heightmap, ++depth);
                }
                else if (mNE->mBoundary.IsConstained(qPoint))
                {
                    qPoint->SetEndNodeXZ(mNE->GetBoundary().GetX(), mNE->GetBoundary().GetZ());
                    mNE->insertNode(qPoint, heightmap, ++depth);
                }
                else if (mSW->mBoundary.IsConstained(qPoint))
                {
                    qPoint->SetEndNodeXZ(mSW->GetBoundary().GetX(), mSW->GetBoundary().GetZ());
                    mSW->insertNode(qPoint, heightmap, ++depth);
                }
                else if (mSE->mBoundary.IsConstained(qPoint))
                {
                    qPoint->SetEndNodeXZ(mSE->GetBoundary().GetX(), mSE->GetBoundary().GetZ());
                    mSE->insertNode(qPoint, heightmap, ++depth);
                }
            }
        }
    }

}