#include "heightmap/include/QuadtreeNode.h"

int main()
{
    clock_t start;
    clock_t end;

    float X = 2.0f;
    float MIN_Y = -1.0f;
    float MAX_Y = 1.0f;
    int DEPTH = 6;
    camel::Boundary boundary(X, MIN_Y, MAX_Y);
	camel::HeightmapNode heightmap;
    camel::QuadtreeNode qt(&heightmap, boundary, DEPTH);

    float cameraAngle = -45.0f;

    // ----- Read PCD file -----
    std::cout << "Read PCD File : ";

    std::string inputPath = "/home/wj/Desktop/Data/input_data/stair_real.pcd";
    start = clock();

    std::vector<camel::Point3D*> inputPoints = qt.ReadPCDToVector(inputPath, cameraAngle);

    end = clock();
    std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;


    // ----- sampling -----
    std::cout << "Sampling : ";
    start = clock();

    std::vector<camel::Point3D*> samplingPoints = qt.SamplingPoints(inputPoints, 5000);

    end = clock();
    std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;


//     ----- Insert in Quadtree -----
    std::cout << "Insert in Quadtree : ";

    start = clock();

    qt.InsertPoints(samplingPoints);

    end = clock();
    std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;


    // ----- Make HeightmapNode -----
    std::cout << "Make HeightmapNode : ";

    start = clock();

	heightmap.MakeMapToVector();

    end = clock();
    std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;


    // ----- Write PCD file -----
    std::cout << "Write PCD File : ";
    start = clock();

    std::string outputPath = "/home/wj/Desktop/Data/output_data/";

	heightmap.WriteVectorToPCD(outputPath);
    end = clock();
    std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;
}