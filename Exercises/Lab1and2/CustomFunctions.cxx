#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

// function to read 2D (x,y) pairs from a file and return a vector of pairs
// file and data are passed as output parameters
bool read_2D_coords_from_file(const std::string& file, 
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
    bool not_negative=false;
    std::string user_input;
    // Request user to give number of lines to read
    std::cout << "Please enter the number of lines to be printed" << std::endl;

    std::cin >> user_input;
    N = std::stoi(user_input);
    std::cout << "Requested " << N << " lines to be printed" << std::endl;
    
    
    // I'm not sure why they would ask for negative lines
    // but might as well check for it
    while (!not_negative) {
        if (N < 0) {
            std::cout << "Please enter a positive integer number of lines" << std::endl;
            std::cin >> user_input;
            N = std::stoi(user_input);
            std::cout << "Requested " << N << " lines to be printed" << std::endl;
        }
        else{
            not_negative = true;
        }
    }
    
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


int least_squares_fit(const std::string& data_file, double& gradient, double& intercept) {

    std::vector<std::pair<double, double>> data;
    double sum_x = 0.0;
    double sum_y = 0.0;
    double sum_sq_x = 0.0;
    double sum_xy = 0.0;
    
    
    if (!read_2D_coords_from_file(data_file, data)) {
        return -1;
    }
    
    const double N = static_cast<double>(data.size()); // make sure N is cast as double

    for (const auto& point : data) { // loop over all data in vector
        const double x = point.first;
        const double y = point.second;
        
        sum_x += x;
        sum_y += y;
        sum_sq_x += x*x;
        sum_xy += x*y;
        
    }
    const double denom = N * sum_sq_x - sum_x * sum_x;
    if (denom == 0.0) {
        return -1;   // all x equal (or no data)
    }
    
    gradient = ( N*sum_xy - sum_x*sum_y ) / denom;
    intercept = ( sum_sq_x*sum_y - sum_xy*sum_x ) / denom;
    
    
    return 0;

}

void get_user_choice(int& user_choice) {

    std::string user_input;
    std::cout << "Which task would you like to perform?" << std::endl;
    std::cout << "1 - Print N lines of data" << std::endl;
    std::cout << "2 - Print magnitude of all data points" << std::endl;
    std::cout << "3 - Least squares fit with Chi^2" << std::endl;
    std::cin >> user_input;
    user_choice = std::stoi(user_input);
    
}