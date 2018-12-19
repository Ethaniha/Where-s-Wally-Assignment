//
//  NNSPrototype.hpp
//  WhereTheFuckWally
//
//  Created by Ethan Richardson on 12/12/2018.
//  Copyright © 2018 Ethan Richardson. All rights reserved.
//

#ifndef NNSPrototype_hpp
#define NNSPrototype_hpp

#include <stdio.h>
#include <vector>
using namespace std;

class algorithms {
private:
//    vector<int> highScoreX;
//    vector<int> highScoreY;
//    vector<int> highScoreTracker;
public:
    double* NNS(vector<vector<int>> OGMatrixScene, vector<vector<int>> OGMatrixWally);
    double* SSDNNS(vector<vector<int>> OGMatrixScene, vector<vector<int>> OGMatrixWally);
    void NNSMain(vector<vector<int>> OGMatrixScene, vector<vector<int>> OGMatrixWally);
    vector<int> vectorSampler(vector<vector<int>>, int offsetCol, int offsetRow);
    //void highScore(int type, int score);
};

#endif /* NNSPrototype_hpp */
