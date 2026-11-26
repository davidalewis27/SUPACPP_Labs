// AnalyseData.cxx
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

int main()
{
    std::string input_file = "input2D_float.txt";
    std::string error_file = "error2D_float.txt";
    std::string output_directory = "Outputs/";
    int user_choice;
    std::vector<std::pair<double, double>> data;
    double gradient, intercept;
    bool running = true;
    
    if (!read_2D_coords_from_file(input_file, data)) {
        return -1;
    }
    
    while (running) {
        get_user_choice(user_choice);
        switch (user_choice) {
            
            case 0: {
                std::cout << "Exiting." << std::endl;
                running = false;
            break;
            
            }
            case 1: {
                std::cout << "Requested task: 1" << std::endl;
                int N_lines;
                get_number_of_lines(N_lines);
                
                // Check if number of lines requested > total
                if (N_lines > static_cast<int>(data.size())) {
                    std::cout << "Requested more than total lines (" << data.size() << "), printing only first 5..." << std::endl;
                    N_lines=std::min<int>(5, data.size()); // overwrite user input to be 5 lines, or data length if < 5
                } 
                
                write_data(data, std::cout, N_lines);
                
                // wasn't sure if this also needed written to file
                // so I'll do it just in case
                std::string selected_N_file = "selected_N_data.txt";
                std::ofstream out_stream;
                // Open the file
                out_stream.open(output_directory + selected_N_file);
                write_data(data, out_stream, N_lines);
                out_stream.close();
                break;
            }
            case 2: {
                int N_points;
                double x;
                double y;
                std::vector<double> vector_magnitudes;
                double mag=0.0;
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
                
                
                std::string vector_mag_file = "vector_magnitudes.txt";
                std::ofstream out_stream;
                // Open the file
                out_stream.open(output_directory + vector_mag_file);
                write_data(vector_magnitudes, out_stream);
                out_stream.close();
                break;
            } 
            
            case 3: {
                std::cout << "Requested task: 3" << std::endl;
                least_squares_fit(input_file,gradient,intercept);
                break;
            }    
            
            case 4:  {
                std::cout << "Requested task: 4" << std::endl;
                least_squares_fit(input_file,gradient,intercept,output_directory+"least_squares_fit.txt",error_file);
                break;
            }
            
            case 5: {
                int N_points;
                double x;
                double y;
                std::cout << "Requested task: 5" << std::endl;
                N_points = data.size();
                double func_val;
                std::vector<double> x_pow_ys;
                for (int i=0; i<N_points; i++){
                    x = data[i].first;
                    y = data[i].second;
                    
                    func_val = recursive_self_multiply(x,y);
                    x_pow_ys.push_back(func_val);
                }
                write_data(x_pow_ys, std::cout);
                std::string x_exp_y_file = "x_pow_y.txt";
                std::ofstream out_stream;
                out_stream.open(output_directory + x_exp_y_file);
                write_data(x_pow_ys, out_stream);
                out_stream.close();
                break;
            }
            
            default : {
                std::cout << "Unrecognised task number: " << user_choice << std::endl;
            }
        
        }
    }

    return 0;

}