//
// Created by Patrick Gemperline on 10/22/17.
//

#include <cv.h>
#include "ImageReader.h"

using namespace cv;
using namespace std;


ImageReader::ImageReader(){
    inputFile="";
    inputFolder="";
}


ImageReader::ImageReader(String newInputFolder){
    inputFile="";
    inputFolder=newInputFolder;
}


void ImageReader::setInputFile(String newInputFile){
    inputFile=newInputFile;
}

void ImageReader::setInputFolder(String newInputFolder){
    inputFolder=newInputFolder;
}

void ImageReader::setImageHeight(double newHeight) {
    imageHeight=newHeight;
}

void ImageReader::setImageWidth(double newWidth) {
    imageWidth=newWidth;
}


vector< double > ImageReader::readFile()
{

    Mat inputMatrix = imread(inputFile, CV_LOAD_IMAGE_UNCHANGED);

    if (inputMatrix.empty()) //check whether the image is loaded or not
    {
        cout << "Error : Image cannot be loaded..!!" << endl;

        vector<double> empty;

        return empty;
    }

    inputMatrix = rescaleMat(inputMatrix);

    return MatToVector(inputMatrix);

}


vector<vector<double> > ImageReader::readFolder(){
    
    if (inputFolder.empty()) //check whether the image is loaded or not
    {
        cout << "Error : Image cannot be loaded.. (no folder name)!!" << endl;

        vector<vector<double> > empty;

        return empty;
    }

    vector < string > fileList = getFileNames(inputFolder);

    int fileCounter=0;

    int numberOfFiles=fileList.size();

    ImageReader temp;

    temp.setImageWidth(imageWidth);

    temp.setImageHeight(imageHeight);

    vector <double> tempImageData;

    vector< vector < double > > imageVectors;

    while (fileCounter<numberOfFiles){


        if(fileList[fileCounter].empty()){
            break;
        }

        temp.setInputFile(fileList[fileCounter]);
        
        tempImageData=temp.readFile();

        if (tempImageData.size()>0){

            cout << fileList[fileCounter] << endl;

            imageVectors.push_back(tempImageData);
        }

        fileCounter++;

    }

    return imageVectors;
}






/*
 * Helper Functions
 */
vector<double> ImageReader::MatToVector(Mat inputMatrix){

    vector<uchar> bgrVector;
    vector<double> returnVector;
    if (inputMatrix.isContinuous()) {

        bgrVector.assign(inputMatrix.datastart, inputMatrix.dataend);

    }

    else {

        for (int i = 0; i < inputMatrix.rows; ++i) {

            bgrVector.insert(bgrVector.end(), inputMatrix.ptr<uchar>(i), inputMatrix.ptr<uchar>(i)+inputMatrix.cols);

        }

    }

    for(int i = 0; i<bgrVector.size(); i++){

        returnVector.push_back(((double) bgrVector[i] / (double) 255 ) + (double).01);
    }


    return returnVector;
}


vector< string > ImageReader::getFileNames(string inputFolder){

    string path= inputFolder;
    
      string callString="./listFiles.sh "+path;
  
      const char* passString=callString.c_str();
      
      system(passString);

      std::ifstream inputFile;
  
      string fileNames="fileNames.txt";
  
      inputFile.open(fileNames.c_str());
  
      string inputLine;
      
      vector<string> fileList;
  
      while (inputFile.peek() && !inputFile.eof())
      {
        getline(inputFile,inputLine);

        fileList.push_back(inputLine);

      }

      inputFile.close();

      return fileList;
}

Mat ImageReader::rescaleMat(Mat rawMat){

    Mat scaledMat = Mat((int)100, (int)100, CV_8UC3);


    double widthScale = imageWidth / (double)rawMat.cols;
    double heightScale = imageHeight / (double)rawMat.rows;

    cv::resize(rawMat, scaledMat, Size(), widthScale, heightScale, INTER_AREA);


    return scaledMat;
}