#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

// function to read 2D (x,y) pairs from a file and return a vector of pairs
// file and data are passed as output parameters
bool read_2D_coords_from_file(std::string& file, 
                              std::vector<std::pair<double, double>>& data) 
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

    while (std::getline(data_file, xi, ',')) {         
        std::getline(data_file, yi); // xi, yi are strings
        data.push_back( {std::stod(xi), std::stod(yi)} );

    }    

    // Close the file
    data_file.close();
    std::cout << "File: " << file << " closed" << std::endl;

    return true;
}


void write_data_to_terminal(const std::vector<std::pair<double, double>>& data) {
    int N;
    std::string user_input;
    // Request user to give number of lines to read
    std::cout << "Please enter the number of lines to be printed" << std::endl;

    std::cin >> user_input;
    N = std::stoi(user_input);
    std::cout << "Requested " << N << " lines to be printed" << std::endl;

    if (N > data.size()) {
        std::cout << "Requested more than total lines (" << data.size() << "), printing only first 5..." << std::endl;
        N=5;
    } 

    for (int i=0; i<N; i++){
        std::cout << data[i].first << " " << data[i].second << std::endl;
    }
}


double two_component_vector_magitude(double x, double y) {
    
    double vector_magnitude;
    
    vector_magnitude = std::sqrt(x*x + y*y);

    return vector_magnitude;
}