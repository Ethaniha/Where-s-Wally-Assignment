//
//  main.cpp
//  WhereTheFuckWally
//
//  Created by Ethan Richardson on 30/11/2018.
//  Copyright © 2018 Ethan Richardson. All rights reserved.
//
#include "NNSPrototype.hpp"
#include "baseImage.hpp"
#include "largeImage.hpp"
#include "refImage.hpp"
#include "matrix.hpp"
#include <vector>
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
using namespace std;

int main() {
    
    //1024c 768r for large // 49r 36c for wally
    
    //VARIABLES & INITIALISING
    refImage wallyRW;largeImage sceneRW;baseImage NNSRW;                                       //Generating seperate objects of class readWrite for both Wally and Scene
    algorithms Algorithms;
    matrixConvert matrixConvertWally;matrixConvert matrixConvertScene;          //Generating seperate objects of class readWrite for both Wally and Scene
    vector<vector<int>> matrixWally;vector<vector<int>> matrixScene;            //Generating 2D vectors of type INT to store values passed by reference from matrixConvert
    int rowsW = 49;int columnsW = 36;                                           //Wally Size
    int rowsS = 768;int columnsS = 1024;                                        //Scene Size
    string wallyAddress = "../../Assessment_Files/Wally_grey";                  //Creating string path for Wally to pass into fileAddresser to generate .txt & .pgm versions
    string sceneAddress = "../../Assessment_Files/Cluttered_scene";             //Creating string path for Scene to pass into fileAddresser to generate .txt & .pgm versions
    string NNSAddress = "../../Assessment_Files/NNS";
    char* wallyAddressTXT = new char[wallyAddress.length()];char* wallyAddressPGM = new char[wallyAddress.length()];  //Creating char* to store the completed file addresses for Wally
    char* sceneAddressTXT = new char[sceneAddress.length()];char* sceneAddressPGM = new char[sceneAddress.length()];  //Creating char* to store the completed file addresses for Scene
    char* NNSAddressTXT = new char[NNSAddress.length()];char* NNSAddressPGM = new char[NNSAddress.length()];
    clock_t clkStart;
    clock_t clkFinish;
    
    //Title
    NNSRW.titleOutput();
    
    clkStart = clock();
    //GENERATING FILE PATHS
    wallyRW.fileAddresser(wallyAddress, wallyAddressTXT, wallyAddressPGM);
    sceneRW.fileAddresser(sceneAddress, sceneAddressTXT, sceneAddressPGM);
    NNSRW.fileAddresser(NNSAddress, NNSAddressTXT, NNSAddressPGM);
    
    //READING
    double* wallyData = wallyRW.read_text(wallyAddressTXT, rowsW, columnsW);
    double* sceneData = sceneRW.read_text(sceneAddressTXT, rowsS, columnsS);
    
    //WRITING
    wallyRW.write_pgm(wallyAddressPGM, wallyData, rowsW, columnsW, 255);
    sceneRW.write_pgm(sceneAddressPGM, sceneData, rowsS, columnsS, 255);
    
    //MATRIX
    matrixConvertWally.Array2D(wallyData, rowsW, columnsW, &matrixWally);
    matrixConvertScene.Array2D(sceneData, rowsS, columnsS, &matrixScene);
    
    double* NNSdata = Algorithms.NNS(matrixScene, matrixWally);
    //Algorithms.NNSMain(matrixScene, matrixWally);
    NNSRW.write_pgm(NNSAddressPGM, NNSdata, rowsS, columnsS, 255);
    clkFinish = clock() - clkStart;
    cout << endl << "Program completed in: " << ((float)clkFinish/CLOCKS_PER_SEC) << " seconds!" << endl;
    //Making some sick edits
    return 0;
}

