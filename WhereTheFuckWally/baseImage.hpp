//
//  baseImage.hpp
//  WhereTheFuckWally
//
//  Created by Ethan Richardson on 30/11/2018.
//  Copyright © 2018 Ethan Richardson. All rights reserved.
//

#ifndef baseImage_hpp
#define baseImage_hpp

#include <stdio.h>
#include <string>
#include <string>
using namespace std;

class baseImage {
private:
    
public:
    
    void titleOutput();
    void fileAddresser(string filename, char *source, char *source2);
    double* read_text(char *fileName, int sizeR, int sizeC);
    void write_pgm(char *filename, double *data, int sizeR, int sizeC, int Q);
    
};
#endif /* baseImage_hpp */
