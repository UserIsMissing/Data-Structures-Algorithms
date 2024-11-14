/*
Cole Schreiner
caschrei
pa8
WordFrequency.cpp
*/


#include "Dictionary.h"
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char *argv[])
{
    // Check for correct number of arguments
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Open input file
    std::ifstream in(argv[1]);
    if (!in)
    {
        std::cerr << "Unable to open file " << argv[1] << std::endl;
        exit(EXIT_FAILURE);
    }
    // Open output file
    std::ofstream out(argv[2]);
    if (!out)
    {
        std::cerr << "Unable to open file " << argv[2] << std::endl;
        exit(EXIT_FAILURE);
    }

    // Create Dictionary object
    Dictionary D;
    std::string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    std::string word;
    std::string key;
    size_t begin, end, length;

    // Read lines
    while (getline(in, word))
    {
        length = word.length();

        // Get first key
        begin = std::min(word.find_first_not_of(delim, 0), length);
        end = std::min(word.find_first_of(delim, begin), length);
        key = word.substr(begin, (end - begin));

        // Key found
        while (key != "")
        {
            // Convert key to lower case
            for (size_t i = 0; i < key.length(); i++)
            {
                key[i] = tolower(key[i]);
            }

            // Add to dictionary
            if (D.contains(key))
            {
                D.setValue(key, D.getValue(key) + 1);
            }
            else
            {
                D.setValue(key, 1);
            }

            // Get next token
            begin = std::min(word.find_first_not_of(delim, (end + 1)), length);
            end = std::min(word.find_first_of(delim, begin), length);
            key = word.substr(begin, (end - begin));
        }
    }

    // Write Dictionary to output file
    out << D.to_string() << std::endl;

    // Close files
    D.clear();
    in.close();
    out.close();

    return EXIT_SUCCESS;
}