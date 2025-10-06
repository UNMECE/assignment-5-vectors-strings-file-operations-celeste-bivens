#include <iostream>
#include <fstream>//look into sstream library.
#include <vector>
#include <random>
#include <string>
#include "pixel.h"


void average_colors(std::vector<Pixel> &pixel_list){
    float total_r = 0.0;
    float total_g = 0.0; 
    float total_b = 0.0;

    for (const Pixel &p : pixel_list){//Using ':' operator to seperate the loop variable from the container I'm iterating over. 
        total_r += p.r;
        total_g += p.g;
        total_b += p.b;
        
    }

    int num_pixels = pixel_list.size();
    if (num_pixels==0){
        std::cout<< "not enough pixel values"<<std::endl;
    }

    double avg_r = total_r/num_pixels;
    double avg_g = total_g/num_pixels;
    double avg_b = total_b/num_pixels;



    std::cout << "Average r: " << avg_r << std::endl;
    std::cout << "Average g: " << avg_g << std::endl;
    std::cout << "Average b: " << avg_b <<std:: endl;

}

void flip_vertically(std::vector<Pixel>& pixel_list){

    if (pixel_list.empty()) 
        return;

    auto forwardIndex = 0;
    auto reverseIndex = pixel_list.size() - 1;

    while(forwardIndex < reverseIndex){

        auto &fwdPix = pixel_list[forwardIndex];
        auto &revPix = pixel_list[reverseIndex];

        // auto temp = fwdPix.y;
        // fwdPix.y = revPix.y;
        // revPix.y = temp;
        
        std::swap(fwdPix.y, revPix.y);//using swap operator to swap the y-values.

        forwardIndex++;
        reverseIndex--;
        
    }

}

void save_flipped_pixels(const std::vector<Pixel> &pixel_list, const std::string &filename){

    std::ofstream outfile(filename);

    if (!outfile){
        std::cout<<"Could not open file "<<std::endl;
    }

    for (const Pixel &p : pixel_list){
        outfile << p.x << ","
                << p.y<<","
                << p.r << ","
                << p.g << ","
                << p.b << ","
                <<std::endl;
    }

    outfile.close();//Learned about this at https://cplusplus.com/forum/beginner/205850/ 
    std::cout << "Flipped image saved to " << filename << std::endl;
}

void print_pixels(const std::vector<Pixel> &pixel_list){
     for (const Pixel &p : pixel_list){
        std::cout << p.x << ","
                << p.y<<","
                << p.r << ","
                << p.g << ","
                << p.b << ","
                <<std::endl;
    }
}


int main(int argc, char **argv){


    //in command line, run build-it.sh. Then, type ./random width height > [name of file.dat]
    // > operator in command line writes the values TO the data file.
    //there's a pixel_5x5.dat file because I wanted to test my flip_vertically function on a smaller data set. 

    std::cout<<"Number of arguments: "<< argc <<std::endl;//checking for correct number of command line arguments: 2.
    if (argc != 2){
        std::cout<<"not enough arguments"<<std::endl;
        return 1;
    }

    std::string filename = argv[1];//file name will be the second command line argument.
    std::ifstream infile(filename);//using fstream to read the lines in this file. Reference: https://www.w3schools.com/cpp/ref_fstream_ofstream.asp 

    if(!infile){
        std::cout<< "Error opening: "<< filename <<std::endl;
        return 1;//Error code. 
    }

    std::vector <Pixel> pixel_list;//Step #2: creating a vector named pixel_list, which will store every pixel from the file.
    std::string line;


    while(std::getline(infile,line)){
        //while loop traverses each line in our .dat file and seperates each value BEFORE the next comma. 
        //Step #3: using .substr() and .find() to seperate the values.
        size_t pos1 = (line.find(','));//Finding first occurance of comma.
        int x = stoi(line.substr(0, pos1));

        size_t pos2 = (line.find(',',pos1 + 1));
        int y = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));

        size_t pos3 = (line.find(',', pos2 + 1));
        float r = stof(line.substr(pos2 + 1, pos3 - pos2 - 1));

        size_t pos4 = (line.find(',', pos3 + 1));
        float g = stof(line.substr(pos3 + 1, pos4 - pos3 - 1));

        size_t pos5 = (line.find(',',pos4 + 1));
        float b = stof(line.substr(pos4 + 1, pos5 - pos4 - 1));

        Pixel p;//Parsing through variables in Pixel class, and referencing it using p. 
        p.r = r;
        p.g = g;
        p.b = b;
        p.x = x;
        p.y = y;

        pixel_list.push_back(p);//Using push_back to store each object back into Pixel class. 
    }

    std::cout << "Read " << pixel_list.size() << " pixels" << std::endl;//Reading each line/size of line. 
    std::cout <<"====================="<<std::endl;

    std::cout<<"Average for r,g,b values: "<<std::endl;
        average_colors(pixel_list);//Step #4: creating a find average function. 
    
    std::cout <<"====================="<<std::endl;

    flip_vertically(pixel_list);//Step #4: flipping verticallly function
    save_flipped_pixels(pixel_list,"flipped.dat");//Writing these new pixels to flipped.dat

    return 0;
}