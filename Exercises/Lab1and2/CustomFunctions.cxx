#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// function to read 2D (x,y) pairs from a file and return a vector of pairs
// file and data are passed as output parameters
bool read_2D_coords_from_file(std::string& file, 
                              std::vector<std::pair<float, float>>& data) 
                              {
    std::ifstream data_file;
    std::string line;
    std::string xi;
    std::string yi;

    // Open the file
    data_file.open(file);


    // Check the file is correctly opened
    // Otherwise, return false to be caught back in main
    if (!data_file.is_open()) {
        std::cout << "Error in opening file: " << file << std::endl;
        return false;
    }
    else {
        std::cout << "File: " << file << " opened successfully" << std::endl;
    }

    // read first line, assume this is header
    std::getline(data_file, line);

    while (data_file >> xi >> yi) {         // xi, yi are strings
        data.push_back( {std::stof(xi), std::stof(yi)} );

    }    

    // Close the file
    data_file.close();
    std::cout << "File: " << file << " closed" << std::endl;

    return true;
}