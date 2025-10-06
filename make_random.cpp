#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "pixel.h"

/* make_random.cpp creates new pixels and arranges them in a grid layout, while writing these values to our .dat files. Using build-it.sh script file 
(to reduce repetitive command line arguments), I am able to customize the exact width and height of my grid for my pixel values.
*/

std::vector<Pixel> generateRandomPixels(int height, int width, int maxPixel = 255){//Pixels range from 0 to 255 generally.

    std::vector<Pixel> pixel_list;
    pixel_list.reserve(width * height);//.reserve() keeps the width and height of the array.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));//creating random unsigned integers using time operator of the ctime library.
    //We want floating point numbers that are unsigned.

    for (int i = 0; i < width; i++)
    {
        for(int j = 0; j < height;j++)
        {
            Pixel p;
            p.x = i;
            p.y = j;
            p.r = (std::rand() % maxPixel) / static_cast<float>(maxPixel);//using rand() to create pixel values and divide by floating point integers.
            p.g = (std::rand() % maxPixel) / static_cast<float>(maxPixel);
            p.b = (std::rand() % maxPixel) / static_cast<float>(maxPixel);
            pixel_list.push_back(p);//Using push_back to add new elements back to container.
        }
    }
    return pixel_list;
}

int main(int argc, char **argv){

    int width = 5;
    int height = 5;

    if (argc >= 3){//looking for three arguments in command line: executable name, the width, and height. 
        width = std::atoi(argv[1]);
        height = std::atoi(argv[2]);//User customizing the width and height of the array.
    }
    std::vector<Pixel> pixel_list = generateRandomPixels(width, height);//calling generateRandomPixels function

    for (const Pixel &p : pixel_list)
    {
        std::cout//printing values
        << p.x << "," << p.y<< "," << p.r << "," << p.g << "," << p.b << ","
            <<std::endl;
    }

    //in command line, run build-it.sh. Then, type ./random width height > [name of file.dat]
    // > operator in command line writes the values to the data file.
}



