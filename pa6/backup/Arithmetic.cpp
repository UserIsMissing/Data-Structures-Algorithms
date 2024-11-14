/*
Cole Schreiner
caschrei
pa6
Arithmetic.cpp
*/

#include "BigInteger.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>

int main(int argc, char* argv[]){
    if(argc != 3){
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::ifstream in(argv[1]);
    if(!in){
        std::cerr << "Unable to open file " << argv[1] << std::endl;
        exit(EXIT_FAILURE);
    }
    std::ofstream out(argv[2]);
    if(!out){
        std::cerr << "Unable to open file " << argv[2] << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string StringA, StringB;
    std::getline(in, StringA);
    std::getline(in, StringB);
    std::getline(in, StringB);
    BigInteger A = BigInteger(StringA);
    BigInteger B = BigInteger(StringB);

    out << A.to_string() << std::endl;
    out << std::endl;
    out << B.to_string() << std::endl;
    out << std::endl;
    out << (A+B).to_string() << std::endl;
    out << std::endl;
    out << (A-B).to_string() << std::endl;
    out << std::endl;
    out << (A-A).to_string() << std::endl;
    out << std::endl;
    out << ((A*3)-(2*B)).to_string() << std::endl;
    out << std::endl;
    out << (A*B).to_string() << std::endl;
    out << std::endl;
    out << (A*A).to_string() << std::endl;
    out << std::endl;
    out << (B*B).to_string() << std::endl;
    out << std::endl;
    out << ((BigInteger("9")*A*A*A*A)+(BigInteger("16")*B*B*B*B*B)).to_string() << std::endl;
    
    in.close();
    out.close();
    return 0;
}