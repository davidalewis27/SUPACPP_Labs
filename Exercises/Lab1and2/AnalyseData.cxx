#include <iostream>  // I/O
#include <vector>    // Vectors
#include <string>    // Strings
#include <utility>   // To use std::pair
#include <fstream>   //
#include <cmath>     //
#include <stdexcept> // Handle exceptions
#include "CustomFunctions.h"  // For custom functions

int main()
{
    std::string input_file = "input2D_float.txt";
    std::string error_file = "error2D_float.txt";
    int user_choice;
    int N_points;
    int N_lines;
    int i;
    double mag;
    double x;
    double y;
    std::vector<std::pair<double, double>> data;
    std::vector<std::pair<double, double>> data_err;
    std::vector<double> vector_magnitudes;
    double gradient, intercept;
    
    
    get_user_choice(user_choice);
    
    if (user_choice == 1) {
        std::cout << "Requested task: 1" << std::endl;
        if (!read_2D_coords_from_file(input_file, data)) {
            return -1;
        }

        get_number_of_lines(N_lines);
        
        // Check if number of lines requested > total
        if (N_lines > data.size()) {
            std::cout << "Requested more than total lines (" << data.size() << "), printing only first 5..." << std::endl;
            N_lines=std::min<int>(5, data.size());; // overwrite user input to be 5 lines, or data length if < 5
        } 
        
        write_data(data, std::cout, N_lines);
    
    }
    else if(user_choice == 2) {
        if (!read_2D_coords_from_file(input_file, data)) {
            return -1;
        }
        N_points = data.size();
        std::cout << "Requested task: 2" << std::endl;
        for (int i=0; i<N_points; i++){
            x = data[i].first;
            y = data[i].second;
            mag = two_component_vector_magitude(x,y);
            // std::cout << "vec = (" << x << "," << y << ") --> magnitude = " << mag << std::endl;
            vector_magnitudes.push_back(mag);
        }
        write_data(vector_magnitudes, std::cout, N_points);
    }
    else if(user_choice == 3) {
        std::cout << "Requested task: 3" << std::endl;
        least_squares_fit(input_file,gradient,intercept);
        // std::cout << "Least squares fit: y = " << gradient << " x + " << intercept << std::endl;   
    }
    else if(user_choice == 4) {
        std::cout << "Requested task: 4" << std::endl;
        least_squares_fit(input_file,gradient,intercept,error_file);
    }
    else if(user_choice == 5) {
        std::cout << "Requested task: 5" << std::endl;
        if (!read_2D_coords_from_file(input_file, data)) {
            return -1;
        }
        N_points = data.size();
        double func_val;
        std::vector<double> x_pow_ys;
        for (int i=0; i<N_points; i++){
            x = data[i].first;
            y = data[i].second;
            
            func_val = recursive_self_multiply(x,y);
            std::cout << func_val << std::endl;
            x_pow_ys.push_back(func_val);
            
        }
        
    
    }
    else{
        std::cout << "Unrecognised task number: " << user_choice << std::endl;
    
    }


    return 0;

}