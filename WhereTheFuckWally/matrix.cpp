//
//  matrix.cpp
//  WhereTheFuckWally
//
//  Created by Ethan Richardson on 30/11/2018.
//  Copyright © 2018 Ethan Richardson. All rights reserved.
//

#include "matrix.hpp"
#include <vector>
#include <iostream>
using namespace std;

void matrixConvert::Array2D(double *data, int rows, int columns, vector<vector<int>>* stuff) {
    
    //FILL
    int k = 0;
    for(int i = 0; i < rows; i++) {
        vector<int> temp;
        for(int j = 0; j < columns; j++) {
            temp.push_back(data[k]);
            //cout << temp[j] << " ";
            k++;
            //cout << " k = " << k << " ";
        }
        stuff->push_back(temp);
    }
    
//    //PRINT
//    for(int j = 0; j < (rows*columns); j++) {
//            cout << data[j] << " ";
//        }
//        cout << endl;
//        cout << endl;
    
}
void matrixConvert::VerboseArray2D(double *data, int rows, int columns, vector<vector<int>>* stuff) {
    
    //FILL
    int k = 0;
    for(int i = 0; i < columns; i++) {
        vector<int> temp;
        for(int j = 0; j < rows; j++) {
            temp.push_back(data[k]);
            //cout << temp[j] << " ";
            k++;
            //cout << " k = " << k << " ";
        }
        stuff->push_back(temp);
    }
    cout << endl;
    cout << endl;
    
    //    //PRINT
        for(int j = 0; j < (rows*columns); j++) {
                cout << data[j] << " ";
            }
            cout << endl;
            cout << endl;
    
}
