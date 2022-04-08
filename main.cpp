#include "heightmap.h"

int main()
{
    clock_t start;
    clock_t end;

    float MIN_X = -1.0f;
    float MAX_X = 1.0f;
    float Z = 2.0f;
    int DEPTH = 6;
    quadtree::Boundary boundary(MIN_X, MAX_X, Z);
    quadtree::Node qt(boundary, DEPTH);
    quadtree::Heightmap* heightmap = new quadtree::Heightmap();
    qt.SetHeightmap(heightmap);


    // ----- Read PCD file -----
    std::cout << "Read PCD File : ";

    std::string inputPath = "/home/wj/Desktop/Data/input_data/stair_real.pcd";
    start = clock();

    std::vector<quadtree::Point3D*> inputPoints = qt.ReadPCDToVector(inputPath);

    end = clock();
    std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec \t" << inputPoints.size() << std::endl;

    // ----- sampling -----
    std::cout << "Sampling : ";
    start = clock();

    std::vector<quadtree::Point3D*> samplingPoints = qt.SamplingPoints(inputPoints, 5000);

    end = clock();
    std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec \t" << samplingPoints.size() << std::endl;

    // ----- Get Height -----
    std::cout << "Get Heightmap : ";

    start = clock();

    qt.InsertPoints(samplingPoints);

    end = clock();
    std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec \t" << samplingPoints.size() << std::endl;

    // ----- Write PCD file -----
    std::cout << "Write PCD File : ";
    start = clock();

    std::string outputPath = "/home/wj/Desktop/Data/output_data/";

    qt.WriteVectorToPCD(outputPath);

    end = clock();
    std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec" << std::endl;

//    time_t t;
//    struct tm* timeinfo;
//    time(&t);
//    timeinfo = localtime(&t);
//
//    std::string hour, min;
//
//    if (timeinfo->tm_hour < 10) hour = "0" + std::to_string(timeinfo->tm_hour);
//    else hour = std::to_string(timeinfo->tm_hour);
//
//    if (timeinfo->tm_min < 10) min = "0" + std::to_string(timeinfo->tm_min);
//    else min = std::to_string(timeinfo->tm_min);
//
//    std::string filePath = outputPath + hour + min + ".pcd";
//
//    std::ofstream fout;
//    fout.open(filePath);
//
//    fout << "VERSION" << std::endl;
//    fout << "FIELDS x y z" << std::endl;
//    fout << "SIZE 4 4 4" << std::endl;
//    fout << "TYPE F F F" << std::endl;
//    fout << "COUNT 1 1 1" << std::endl;
//    fout << "WIDTH 1" << std::endl;
//    fout << "HEIGHT " << samplingPoints.size() << std::endl;
//    fout << "VIEWPOINT 0 0 0 1 0 0 0" << std::endl;
//    fout << "POINTS " << samplingPoints.size() << std::endl;
//    fout << "DATA ascii" << std::endl;
//
//    for (int i = 0; i < samplingPoints.size(); i++)
//    {
//        fout << samplingPoints[i]->GetX() << " " << samplingPoints[i]->GetY() << " " << samplingPoints[i]->GetZ() << "\n";
//    }
//
//    fout.close();
//
//    end = clock();
//    std::cout << ((double)(end - start)) / (long)CLOCKS_PER_SEC << " sec\t" << samplingPoints.size() << std::endl;
//
//    std::cout << "data : " << hour + min + ".pcd" << std::endl;
}