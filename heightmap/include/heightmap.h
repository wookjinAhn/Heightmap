#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <vector>


const double PI = 3.14159265359;
const double D2R = PI / 180;
const double R2D = 180 / PI;

namespace quadtree
{
    class Point2D
    {
    public:
        Point2D() : mX(0), mZ(0) {}
        Point2D(float x, float z) : mX(x), mZ(z) {}

        float GetX() const { return mX; }
        float GetZ() const { return mZ; }

        void SetX(float x) { mX = x; }
        void SetZ(float z) { mZ = z; }

    private:
        float mX, mZ;
    };

    class Point3D
    {
    public:
        Point3D() : mX(0), mY(0), mZ(0) {}
        Point3D(float x, float y, float z) : mX(x), mY(y), mZ(z) {}

        float GetX() const { return mX; }
        float GetY() const { return mY; }
        float GetZ() const { return mZ; }
        Point2D GetEndNodeXZ() const { return mEndNodeXZ; }

        void SetX(float x) { mX = x; }
        void SetY(float y) { mY = y; }
        void SetZ(float z) { mZ = z; }
        void SetXYZ(float x, float y, float z) { mX = x; mY = y; mZ = z; }
        void SetEndNodeXZ(Point2D endNodeXZ) { mEndNodeXZ = endNodeXZ; }
        void SetEndNodeXZ(float x, float z) { mEndNodeXZ.SetX(x); mEndNodeXZ.SetZ(z); }

    private:
        float mX, mY, mZ;
        Point2D mEndNodeXZ;
    };

    class Boundary
    {
    public:
        Boundary() : mX(0), mZ(0), mW(0), mH(0) {}
        Boundary(float x, float z, float w, float h) : mX(x), mZ(z), mW(w), mH(h) {}
        Boundary(float minX, float maxX, float z) : mX((maxX + minX) / 2), mZ(z / 2), mW((maxX - minX) / 2), mH(z / 2) {}

        float GetX() const { return mX; }
        float GetZ() const { return mZ; }
        float GetW() const { return mW; }
        float GetH() const { return mH; }

        void SetBoundary(float x, float z, float w, float h) { mX = x; mZ = z; mW = w; mH = h; }

        bool IsConstained(Point3D* p) const { return (p->GetX() >= mX - mW && p->GetX() < mX + mW && p->GetZ() >= mZ - mH && p->GetZ() < mZ + mH); }

    private:
        float mX, mZ, mW, mH;
    };

    class Heightmap
    {
    public:
        ~Heightmap()
        {
            for (int i = 0; i < mPoints.size(); i++) {
                delete mPoints[i];
            }
            mPoints.clear();
        }
        std::vector<Point3D*> GetPoints() const { return mPoints; }

        void MakeHeightMap(Point3D* points);
        void MakeMapToVector();

    private:
        std::map<std::pair<float, float>, std::pair<float, int>> mMapPair;
        std::vector<Point3D*> mPoints;
    };

    class Node
    {
    public:
        Node(Boundary boundary, int depth, int capacity) : mBoundary(boundary), mDepth(depth), mCapacity(capacity) {}
        Node(Boundary boundary, int depth) : mBoundary(boundary), mDepth(depth) { mCapacity = 1; }
        ~Node()
        {
            for (int i = 0; i < mPoints.size(); i++) {
                delete mPoints[i];
            }
            mPoints.clear();

            delete mHeightmap;
            mHeightmap = nullptr;
        }
        Boundary GetBoundary() const { return mBoundary; }

        void SetBoundary(Boundary boundary) { this->mBoundary = boundary; }
        void SetBoundary(float x, float z, float w, float h) { this->mBoundary.SetBoundary(x, z, w, h); }
        void SetDepth(int depth) { this->mDepth = depth; }
        void SetCapacity(int capacity) { this->mCapacity = capacity; }
        void SetPoints(std::vector<Point3D*> points) { this->mPoints = points; }
        void SetHeightmap(quadtree::Heightmap* heightmap) { mHeightmap = heightmap; }

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

