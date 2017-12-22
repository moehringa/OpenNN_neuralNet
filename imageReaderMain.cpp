/*********************************************************************
It works now nobody touch anything
*********************************************************************/
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include <cstddef>
#include "ImageReader.h"
using namespace std;

string getInput(string prompt){

  string response;

  cout << prompt << endl;

  cin >> response;

  return response;

}

double getTrainingBit(){

    string trainingBitResponse = getInput("Are the files in this folder for positive training or negative training? Type 1 for positive and 0 for negative or 2 for test images");

    double returnBit = stod(trainingBitResponse);

    return returnBit;
}

string getInputFolderPath(){

    string inputFilePath = getInput("What is the file path of the folder that should be converted?");

    return inputFilePath;

}

int getImagesPerFile(){
    string imagesPerFileResponse = getInput("How many images should be stored in a single file?");

    return stoi(imagesPerFileResponse);
}

void getImageDimensions(ImageReader* kevin){
    string dimension = getInput("What should the height of the rescaled image be?");
    kevin -> setImageHeight(stod(dimension));
    dimension = getInput("what should the width of the rescaled image be");
    kevin -> setImageWidth(stod(dimension));

}

int main()
{

    ImageReader* kevin = new ImageReader();

    string inputFolder = getInputFolderPath();

    getImageDimensions(kevin);

    kevin -> setInputFolder(inputFolder);

    vector < vector < double > > imageData = kevin -> readFolder();

    int fileCounter = 1;

    string currentOutFileName;

    string outFileName = getInput("What should be the name of the output file? Do not include extension.");

    int imagesPerFile = getImagesPerFile();

    currentOutFileName = outFileName + to_string(fileCounter) +".dat";

    system(("touch " + currentOutFileName).c_str());

    system(("rm " + currentOutFileName).c_str());

    system(("touch " + currentOutFileName).c_str());



    ofstream outFile;

    outFile.open(currentOutFileName.c_str());

    double trainingBit = getTrainingBit();

    int i=0;
    int j;
    vector < double > temp;

    int iFinal=imageData.size();


    int jFinal;
    int imageCounter = 0;


    while(i<iFinal){

        temp = imageData[i];

        jFinal=temp.size();


        j=0;

        while(j<(jFinal-1)){

            outFile << temp[j] << " ";

            j++;
        }

        outFile<< temp[jFinal-1] << " " << trainingBit <<endl;

        i++;

        if (imageCounter<(imagesPerFile-1)){
            imageCounter++;
        }
        else{

            imageCounter=0;

            fileCounter++;

            if(i<iFinal){
                outFile.flush();

                outFile.close();

                currentOutFileName = outFileName + to_string(fileCounter) + ".dat";

                system(("touch " + currentOutFileName).c_str());

                system(("rm " + currentOutFileName).c_str());

                system(("touch " + currentOutFileName).c_str());

                outFile.open(currentOutFileName.c_str());
            }

        }
    }
    
    outFile.flush();

    outFile.close();

	return 0;
}