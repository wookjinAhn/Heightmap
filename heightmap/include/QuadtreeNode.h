//
// Created by wj on 22. 4. 8..
//

#ifndef HEIGHTMAP_QUADTREENODE_H
#define HEIGHTMAP_QUADTREENODE_H

#include <algorithm>
#include <ctime>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "Point2D.h"
#include "Point3D.h"
#include "Boundary.h"
#include "HeightmapNode.h"

const double PI = 3.14159265359;
const double D2R = PI / 180;
const double R2D = 180 / PI;

namespace camel
{
    class QuadtreeNode
    {
    public:
        QuadtreeNode(Boundary boundary, int depth, int capacity);
        QuadtreeNode(Boundary boundary, int depth);
		QuadtreeNode(HeightmapNode* heightmap, Boundary boundary, int depth, int capacity);
		QuadtreeNode(HeightmapNode* heightmap, Boundary boundary, int depth);
        ~QuadtreeNode();

        Boundary GetBoundary() const;

        void SetBoundary(Boundary const boundary);
        void SetBoundary(float const x, float const z, float const w, float const h);
        void SetDepth(int const depth);
        void SetCapacity(int const capacity);
        void SetHeightmap(camel::HeightmapNode* const heightmap);

        void InsertPoints(std::vector<Point3D*> points);
        std::vector<Point3D*> SamplingPoints(std::vector<Point3D*> inputPoints, int samplingNum);
        std::vector<Point3D*> ReadPCDToVector(const std::string& inputPath);      // modified
        void WriteVectorToPCD(const std::string& outputPath);

    private:
        void subdivide();
        void insertNode(Point3D* p, HeightmapNode* heightmap, int depth);
//        void insertNodeTest(Point3D* p, HeightmapNode& heightmap, int depth);

        HeightmapNode* mHeightmap = nullptr;
        HeightmapNode mHeightmapTest;
        Boundary mBoundary;
        int mCapacity;
        int mDepth;
        bool mbDivided = false;

        std::vector<Point3D*> mPoints;
        std::vector<Point3D*> mCapacityPoints;

        std::unique_ptr<QuadtreeNode> mNW = nullptr;
        std::unique_ptr<QuadtreeNode> mNE = nullptr;
        std::unique_ptr<QuadtreeNode> mSW = nullptr;
        std::unique_ptr<QuadtreeNode> mSE = nullptr;
    };
}
#endif //HEIGHTMAP_QUADTREENODE_H
