// CustomFunctions.cxx
// As part of the SUPACPP Course 2026
// Assignment #1
// Author: David Lewis
// Date (last modified): 26/11/2026

#include <iostream>  // I/O
#include <vector>    // Vectors
#include <string>    // Strings
#include <utility>   // To use std::pair
#include <fstream>   //
#include <cmath>     //
#include <stdexcept> // Handle exceptions
#include "CustomFunctions.h"  // For custom functions

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
    std::cout << "File: " << file << " closed" << "\n" << std::endl;

    return true;
}


void get_number_of_lines(int& N) {
    // Request user to give number of lines to read
    std::cout << "Please enter the number of lines to be printed" << std::endl;
    while (!(std::cin >> N) || N < 0) {
        if (std::cin.eof()) { N = 0; return; }
        std::cout << "Please enter a non-negative whole number" << std::endl;
        std::cin.clear();
        std::string discard;
        std::getline(std::cin, discard);
    }
    
}

// Computed the magnitude of a vector
// assuming (x,y) is position from (0,0)
double two_component_vector_magitude(double x, double y) {
    double vector_magnitude;
    vector_magnitude = std::sqrt(x*x + y*y);
    return vector_magnitude;
}


std::vector<double> compute_two_vector_magnitudes(std::vector<std::pair<double, double>>& data) {
    std::vector<double> vector_magnitudes;
    double x;
    double y;
    double mag = 0.0;
    
    for (int i=0; i<static_cast<double>(data.size()); i++){
        x = data[i].first;
        y = data[i].second;
        mag = two_component_vector_magitude(x,y);
        vector_magnitudes.push_back(mag);
    }
    
    return vector_magnitudes;

}


double chi_squared(const std::vector<double>& obs, const std::vector<double>& expected, const std::vector<double>& errors){

    int N=obs.size();
    double chi = 0.0;
    
    if (obs.size() != expected.size() || obs.size() != errors.size())
        throw std::invalid_argument("chi_squared: size mismatch");
        
        
    for (int i=0; i<N; i++){
        chi += ( (obs[i] - expected[i])*(obs[i] - expected[i]) ) / (errors[i]*errors[i]);
    }
    
    return chi;
}

double linear(double x, double p, double q) {
    return p*x+q;
}

int least_squares_fit(const std::string& data_file, 
                      double& gradient, 
                      double& intercept,
                      const std::string& output_file,
                      const std::string& error_file
                      ){

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
    
    // same denominator in both terms
    const double denom = N * sum_sq_x - sum_x * sum_x;
    if (std::fabs(denom) < 1e-6) {
        std::cout << "WARN: least_squares_fit denominator small (<1e-6), check result carefully \n" << std::endl;
    }
    
    gradient = ( N*sum_xy - sum_x*sum_y ) / denom;
    intercept = ( sum_sq_x*sum_y - sum_xy*sum_x ) / denom;
    
    // Store all lines of the output into a vector of strings
    std::vector<std::string> results;
    results.push_back("y = " + std::to_string(gradient) + " x + " + std::to_string(intercept));

    
     
    // Perfom chi-sqaured only if an error_file is supplied
    if (!error_file.empty()) {
        std::cout << "Error file supplied: " << error_file << "\n" << std::endl;
        std::cout << "Computing chi-squared" << "\n" <<std::endl;
        double chi_sq = 0.0;
    
        std::vector<std::pair<double, double>> data_err;
        double model_i;
        std::vector<double> model;
        std::vector<double> ys;
        std::vector<double> yerrs;
        
        // Read errors file
        if (!read_2D_coords_from_file(error_file, data_err)) {
            return -1;
        }
        
        if (data_err.size() != data.size()) {
            std::cout << "Error file and data file not the same length" << std::endl;
            return -1;
        }
        
        // Compute the expected value from the least squares fit
        for (std::size_t i = 0; i < data.size(); ++i) {
            const double x = data[i].first;
            const double y = data[i].second;
            
            model_i = linear(x,gradient,intercept);
            
            ys.push_back(y);
            model.push_back(model_i);
            yerrs.push_back(data_err[i].second);
            
        }
        
        chi_sq = chi_squared(ys, model, yerrs);
    
        results.push_back("chi-squared = " + std::to_string(chi_sq));
        // Check more than 2 data points, if not, do not computed reduced chi-sq
        if (N <= 2) {
            std::cout << "Two or fewer data points, not computing chi^2/NDOF" << std::endl;
        }
        else {
            double NDOF = N - 2.0;
            results.push_back("NDOF = " + std::to_string(static_cast<int>(NDOF)));
            results.push_back("chi-squared/NDOF = " + std::to_string(chi_sq / NDOF));
        }
    }
    
    write_data(results, std::cout);
    if (!save_to_file(results, output_file)) {
        return -1;
    }
    
    return 0;

}

void get_user_choice(int& user_choice) {

    std::string user_input;
    std::cout << "\n" << std::endl;
    std::cout << "Which task would you like to perform?" << std::endl;
    std::cout << "0 - Exit program" << std::endl;
    std::cout << "1 - Print N lines of data" << std::endl;
    std::cout << "2 - Print magnitude of all data points" << std::endl;
    std::cout << "3 - Least squares fit" << std::endl;
    std::cout << "4 - Least squares fit with chi-squared" << std::endl;
    std::cout << "5 - Compute x^y from data with recursion" << std::endl;
    
    // Keep asking until a valid integer is entered
    while (!(std::cin >> user_choice)) {
        if (std::cin.eof()) {
            std::cout << "End of input, exiting." << std::endl;
            user_choice = 0;
            return;   
        }
        else {
            std::cout << "Invalid integer choice, please try again" << std::endl;
            std::cin.clear();                   // reset the fail state
            std::string discard;
            std::getline(std::cin, discard);    // throw away the rest of the bad line
        }   
    }
    
}


