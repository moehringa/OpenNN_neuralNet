//
// Created by Patrick Gemperline on 10/22/17.
//

#ifndef HEROIN_IMAGEREADER_H
#define HEROIN_IMAGEREADER_H


#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include <cstddef>

using namespace cv;
using namespace std;


class ImageReader
{

private:
    string inputFile;
    
    string inputFolder;

    double imageWidth;

    double imageHeight;

    vector< double > MatToVector(Mat inputMatrix);

    vector< string > getFileNames(string inputFolder);

    Mat rescaleMat(Mat rawMat);


public:
    ImageReader();

    ImageReader(String newInputFolder);

    void setInputFile(String newInputFile);

    void setInputFolder(String newInputFolder);

    void setImageHeight(double newHeight);

    void setImageWidth(double newWidth);

    vector<double> readFile();

    vector < vector < double > > readFolder();

};

#endif //HEROIN_IMAGEREADER_H
