//
//  NNSPrototype.cpp
//  WhereTheFuckWally
//
//  Created by Ethan Richardson on 12/12/2018.
//  Copyright © 2018 Ethan Richardson. All rights reserved.
//

#include "NNSPrototype.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
void algorithms::NNSMain(vector<vector<int>> OGMatrixScene, vector<vector<int>> OGMatrixWally)  {
    int offsetCol = 0, offsetRow = 0;
    vector<int> wallyCompare = vectorSampler(OGMatrixWally, 0, 0);
    double* SSDData = new double[1024*768];
    
    for(int i2 = 0; i2 < 768; i2++)    { //runni
        for(int i = 0; i < 1024; i++) { //Running for number of rows of large image
            int sumSD = 0; //Initialising & resetting sum of squared difference
            //cout << i << " ";
            if(i2 > (768-36) || i > (1024-49))  { //Ensuring sample is not taken to include out of bounds of vector.
                SSDData[i] = 114704100;
            }
            else {
                vector<int> sceneCompare = vectorSampler(OGMatrixScene, offsetCol, offsetRow); //Generating new sample (position changed by offset after each iteration)
                for(int j = 0; j < (36*49); j++)    { //Running for size of REF image
                    int comparison = wallyCompare[j] - sceneCompare[j]; //Difference
                    comparison *= comparison; //Squaring
                    sumSD += comparison; //adding squared difference of individual element to Sum
                }
                SSDData[i] = sumSD; //inputting sum of squared difference of sample chunk into double*
            }
            //cout << offsetRow << " : " << offsetCol << endl;
            offsetCol++; //Increasing row offset
        }
        offsetCol = 0; //Resetting row offset after moving column
        offsetRow++; //Increasing column offset
        cout << i2 << endl; //Outputting row number for DEBUG & progress bar
    }
    cout << (sizeof(SSDData)/sizeof(*SSDData)) << endl; //Outputting size of final double* DEBUG
    
}

vector<int> algorithms::vectorSampler(vector<vector<int>> inputVector, int offsetCol, int offsetRow) {
    vector<int> outputVector;
    //int counter = 0;
    for (int i = 0; i < 36; i++)
    {
        for (int j = 0; j < 49; j++)
        {
            outputVector.push_back(inputVector[i+offsetCol][j+offsetRow]);
            //cout << (j + offsetRow) << " ";
        }
        //counter++;
    }
    //cout << endl << counter << endl;
    //cout << outputVector.size() << endl;
    
    return outputVector;
}

//double* algorithms::SSDNNS(vector<vector<int>> OGMatrixScene, vector<vector<int>> OGMatrixWally) {
//
//
//}











double* algorithms::NNS(vector<vector<int>> OGMatrixScene, vector<vector<int>> OGMatrixWally) {
    
    vector<vector<int>> temp2;
    vector<vector<int>> nns2D;
    double* NNSdata = new double[768*1024];
    int highScore = 0;
    vector<int> highScoreCol, highScoreRow;
    int scoreStore = 0;
    int wallyRows = 49, wallyCols = 36, sceneRows = 768, sceneCols = 1024;
    
    //SORT
    struct myclass {
        bool operator() (int i,int j) { return (i<j);}
    } myobject;
    

    //COMPARISON
    for(int p = 0; p < sceneRows; p++) {    //Start of loop iterating for Scene columns.
        vector<int> rowVector;                                                      //Initialising & resetting vector for storing rows.
        
        for(int o = 0; o < sceneCols; o++) {    //Start of loop iterating for Scene rows.
            scoreStore = 0;                                                         //Storing each search's score
            
            for(int i = 0; i < wallyRows; i++) {    //Start of loop iterating for Wally columns.
                
                for(int j = 0; j < wallyCols; j++) {    //Start of loop iterating for Wally rows.
                    int pi = p + i;
                    int oj = o + j;
                    
                    if(o > (sceneCols-wallyCols) || p > (sceneRows-wallyRows)) {    //Checking if scan goes out of bounds.
                        scoreStore += 0;
                    }
                    else if(OGMatrixWally[i][j] == 255) {                           //Removing pure white from scan.
                        scoreStore += 0;
                        continue;
                    }
                    else if(OGMatrixScene[pi][oj] == OGMatrixWally[i][j]) {         //If elements match, adding 1 to region scoreStore.
                        //cout << "Scene Row & Column: (" << p << ", " << o << ")   Wally Row & Column: (" << i << ", " << j << ")   Matrix values: (" << OGMatrixScene[pi][oj] << " : " << OGMatrixWally[i][j] << ")" << endl;
                        scoreStore += 1;
                    }
                    else                                                            //Catch-all else statement.
                        scoreStore += 0;
                    
                }   //End of loop iterating for Wally rows.
            }   //End of loop iterating for Wally columns.
            
            if (scoreStore > highScore) {
                highScore = scoreStore;                                             //Setting Highscore.
                highScoreCol.push_back(p);
                highScoreRow.push_back(o);
            }
            rowVector.push_back(scoreStore);                                        //Pushing scoreStore into rowvector to create a row.
            
        }   //End of loop iterating for Scene rows.
        nns2D.push_back(rowVector);                                                 //pushing rowVector into 2D array(nns2D) to create matrix of comparison scores.
        
    }   //End of loop iterating for Scene columns.
    
    for(int i = 0; i < nns2D.size(); i++)   {
        for(int j = 0; j < nns2D[i].size(); j++)    {
            if (nns2D[i][j] == highScore)   {
                for(int o = 0; o < 49; o++) {
                    for(int k = 0; k < 36; k++) {
                        if((o > 1 && o < 47) && (k > 1 && k < 34)){
                            continue;
                        }
                        OGMatrixScene[i+o][j+k] = 0;
                        cout << "Drawing box" << " ";
                        
                    }
                }
            }
        }
    }
    
    
    
    
    
    
    
    
    
    //DOUBLE* OUTPUT
    int counter1 = 0;
    //double temp;
    for(int i = 0; i < 768; i++) {
        for(int j = 0; j < 1024; j++) {
            *(NNSdata+counter1) = OGMatrixScene[i][j];
//            temp = nns2D[i][j];
//            temp = temp / highScore;
//            temp *= 255;
//            //cout << (int)temp << ", ";
//            *(NNSdata+counter1) = (int)temp;

            //cout << nns2D[i][j] << " : " << NNSdata[counter1] << ", ";
            counter1++;
        }
    }
    
    //}
    //DEBUG
//    for (int i = 0; i < bigTest.size(); i++)
//    {
//        for (int j = 0; j < bigTest[i].size(); j++)
//        {
//            cout << bigTest[i][j] << + " ";
//        }
//    }
    
    //sort (bigTest.begin(), bigTest.end(), myobject);
//    for (int i = 0; i < scores.size(); i++)
//    {
//        if (!(scores[i] == 0)) {
//        cout << scores[i] << + " ";
//        }
//    }
    
    cout << endl << nns2D.size() << endl;
    
    cout << endl << highScore << endl;
    cout << "High Score Column: (" << highScoreCol.size() << ") & " << "High Score Row: (" << highScoreRow.size() << ")" << endl;
    for (int j = 0; j < highScoreCol.size(); j++)
    {
        cout << highScoreCol[j] << " : " << highScoreRow[j] << endl;
    }
    //cout << endl << temp2.size() << " : " << temp2[1].size() << endl;
    //cout << OGMatrixWally.size() << " : " << OGMatrixWally[1].size() << endl;
    return NNSdata;
}
