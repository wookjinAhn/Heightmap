//
// Created by wj on 22. 4. 8..
//

#ifndef HEIGHTMAP_NODE_H
#define HEIGHTMAP_NODE_H

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
#include "Heightmap.h"

const double PI = 3.14159265359;
const double D2R = PI / 180;
const double R2D = 180 / PI;

namespace quadtree
{
    class Node
    {
    public:
        Node(Boundary boundary, int depth, int capacity);
        Node(Boundary boundary, int depth);
        ~Node();

        Boundary GetBoundary() const;

        void SetBoundary(Boundary const boundary);
        void SetBoundary(float const x, float const z, float const w, float const h);
        void SetDepth(int const depth);
        void SetCapacity(int const capacity);
        void SetPoints(std::vector<Point3D*> const points);
        void SetHeightmap(quadtree::Heightmap* const heightmap);

        void InsertPoints(std::vector<Point3D*> points);
        std::vector<Point3D*> SamplingPoints(std::vector<Point3D*> inputPoints, int samplingNum);
        std::vector<Point3D*> ReadPCDToVector(std::string inputPath);      // modified
        void WriteVectorToPCD(const std::string& outputPath);

    private:
        void subdivide();
        void insertNode(Point3D* p, Heightmap* heightmap, int depth);

        Heightmap* mHeightmap = nullptr;
        Boundary mBoundary;
        int mCapacity;
        int mDepth;
        bool mbDivided = false;

        std::vector<Point3D*> mPoints;
        std::vector<Point3D*> mCapacityPoints;

        std::unique_ptr<Node> mNW = nullptr;
        std::unique_ptr<Node> mNE = nullptr;
        std::unique_ptr<Node> mSW = nullptr;
        std::unique_ptr<Node> mSE = nullptr;
    };
}
#endif //HEIGHTMAP_NODE_H
