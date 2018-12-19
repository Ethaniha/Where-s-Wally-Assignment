//
//  TESTING.cpp
//  WhereTheFuckWally
//
//  Created by Ethan Richardson on 30/11/2018.
//  Copyright © 2018 Ethan Richardson. All rights reserved.
//

#include "baseImage.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unistd.h>
using namespace std;


void baseImage::titleOutput() {
    vector<string> title;
    title.push_back(" ▄█     █▄     ▄█    █▄       ▄████████    ▄████████    ▄████████    ▄████████       ▄█     █▄     ▄████████  ▄█        ▄█       ▄██   ▄   ");
    title.push_back("███     ███   ███    ███     ███    ███   ███    ███   ███    ███   ███    ███      ███     ███   ███    ███ ███       ███       ███   ██▄ ");
    title.push_back("███     ███   ███    ███     ███    █▀    ███    ███   ███    █▀    ███    █▀       ███     ███   ███    ███ ███       ███       ███▄▄▄███ ");
    title.push_back("███     ███  ▄███▄▄▄▄███▄▄  ▄███▄▄▄      ▄███▄▄▄▄██▀  ▄███▄▄▄       ███             ███     ███   ███    ███ ███       ███       ▀▀▀▀▀▀███ ");
    title.push_back("███     ███ ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀     ▀▀███▀▀▀▀▀   ▀▀███▀▀▀     ▀███████████      ███     ███ ▀███████████ ███       ███       ▄██   ███ ");
    title.push_back("███     ███   ███    ███     ███    █▄  ▀███████████   ███    █▄           ███      ███     ███   ███    ███ ███       ███       ███   ███ ");
    title.push_back("███ ▄█▄ ███   ███    ███     ███    ███   ███    ███   ███    ███    ▄█    ███      ███ ▄█▄ ███   ███    ███ ███▌    ▄ ███▌    ▄ ███   ███ ");
    title.push_back(" ▀███▀███▀    ███    █▀      ██████████   ███    ███   ██████████  ▄████████▀        ▀███▀███▀    ███    █▀  █████▄▄██ █████▄▄██  ▀█████▀  ");
    title.push_back("                                          ███    ███                                                         ▀         ▀                   ");
    
    for(int i = 0; i < 9; i++) {
        cout << title[i] << endl;
        //sleep(1);
    }
}

void baseImage::fileAddresser(string filename, char *source, char *source2) {
    
    strcpy(source, (filename+".txt").c_str());
    strcpy(source2, (filename+".pgm").c_str());
    
}

// Reads .txt file representing an image of R rows and C Columns stored in filename
// and converts it to a 1D array of doubles of size R*C
// Memory allocation is performed inside readTXT
// Read .txt file with image of size (R rows x C columns), and convert to an array of doubles
double* baseImage::read_text(char *fileName, int sizeR, int sizeC)
{
    double* data = new double[sizeR*sizeC];
    int i=0;
    ifstream myfile (fileName);
    if (myfile.is_open())
    {
        
        while ( myfile.good())
        {
            if (i>sizeR*sizeC-1) break;
            myfile >> *(data+i);
            //cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out.
            i++;
        }
        myfile.close();
    }
    
    else cout << "Unable to open file";
    //cout << i;
    
    //cout << *data << endl;
    return data;
}



// Converts a 1D array of doubles of size R*C to .pgm image of R rows and C Columns
// and stores .pgm in filename
// Use Q = 255 for greyscale images and 1 for binary images.
void baseImage::write_pgm(char *filename, double *data, int sizeR, int sizeC, int Q)
{
    
    int i;
    unsigned char *image;
    ofstream myfile;
    
    image = (unsigned char *) new unsigned char [sizeR*sizeC];
    
    // convert the integer values to unsigned char
    
    for(i=0; i<sizeR*sizeC; i++)
        image[i]=(unsigned char)data[i];
    
    myfile.open(filename, ios::out|ios::binary|ios::trunc);
    
    if (!myfile) {
        cout << "Can't open file: " << filename << endl;
        exit(1);
    }
    
    myfile << "P5" << endl;
    myfile << sizeC << " " << sizeR << endl;
    myfile << Q << endl;
    
    myfile.write( reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));
    
    if (myfile.fail()) {
        cout << "Can't write image " << filename << endl;
        exit(0);
    }
    
    myfile.close();
    
    delete [] image;
    
}
