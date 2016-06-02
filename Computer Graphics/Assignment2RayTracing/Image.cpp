#include <iostream>
#include <fstream>
#include "Image.h"
using namespace std;


void Image::read_bmp_file(char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    width = *(int*)&info[18];	
    height = *(int*)&info[22];

    int size = 3 * width * height;

    data = new unsigned char[size]; // allocate 3 bytes per pixel
    // printf("%d\n", size);
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

	for(i = 0; i < size; i += 3)
        {
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
        }


    /*Now data should contain the (R, G, B) values of the pixels. The color of pixel (i, j) is stored at 
    data[j * 3* width + 3 * i], data[j * 3 * width + 3 * i + 1] and data[j * 3 * width + 3*i + 2].

    In the last part, the swap between every first and third pixel is done because windows stores the 
    color values as (B, G, R) triples, not (R, G, B).*/

};

