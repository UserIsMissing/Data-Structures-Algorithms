/*
Cole Schreiner
caschrei
pa7
Order.cpp
*/


#include "Dictionary.h"
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>


int main (int argc, char* argv[])
{
    // Check for correct number of arguments
    if(argc != 3){
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Open input file
    std::ifstream in(argv[1]);
    if(!in){
        std::cerr << "Unable to open file " << argv[1] << std::endl;
        exit(EXIT_FAILURE);
    }
    // Open output file
    std::ofstream out(argv[2]);
    if(!out){
        std::cerr << "Unable to open file " << argv[2] << std::endl;
        exit(EXIT_FAILURE);
    }

    // Create Dictionary object
    Dictionary D = Dictionary();

    // Read in lines of input file
    std::string key = "";
    int val = 1;
    while (std::getline(in, key))
    {
        D.setValue(key, val);
        val++;
    }

    // Write Dictionary to output file
    out << D.to_string() << std::endl;
    out << D.pre_string() << std::endl;

    D.clear();

    // Close files
    in.close();
    out.close();

    return 0;
}
