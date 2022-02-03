#include "quadtree.h"

int main()
{
    float MIN_X = -1.0f;
    float MAX_X = 1.0f;
    float Z = 2.0f;
    int DEPTH = 6;
    QBoundary boundary(MIN_X, MAX_X, Z);
    QNode qt(boundary, DEPTH);

    clock_t start;
    clock_t end;

    // ----- Read PCD file -----
    std::cout << "Read PCD File : ";

    std::string inputPath = "/home/wj/Desktop/Data/input_data/stair_real_rotated.pcd";
    start = clock();

    std::vector<QPoint3D*> inputPoints = qt.ReadPCDToVector(inputPath);

    end = clock();
    std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;

    // ----- sampling -----
    std::cout << "Sampling : ";
    start = clock();

    std::vector<QPoint3D*> samplingPoints = qt.SamplingPoints(inputPoints, 5000);

    end = clock();
    std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;

    // ----- Get Height -----
    std::cout << "Get Heightmap : ";

    start = clock();

    qt.InsertPoints(samplingPoints);

    end = clock();
    std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;

    // ----- Write PCD file -----
    std::cout << "Write PCD File : ";

    std::string outputPath = "/home/wj/Desktop/Data/output_data/";
    start = clock();

    //heightmap->writeMapToPCD(outputPath);
    //Heightmap.GetHeightmap()->writeMapToPCD(outputPath);
    qt.WriteVectorToPCD(outputPath);

    end = clock();
    std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;
}