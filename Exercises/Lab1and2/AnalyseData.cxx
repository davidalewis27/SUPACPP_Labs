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
#include <filesystem> // to make Outputs/ if it doesnt exist
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
    
    try {
        std::filesystem::create_directories(output_directory);
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cout << "Could not create output directory: " << e.what() << std::endl;
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
                save_to_file(data, output_directory+"selected_N_lines.txt", N_lines);
                break;
            }
            case 2: {

                std::vector<double> vector_magnitudes;
                std::cout << "Requested task: 2" << std::endl;
                vector_magnitudes = compute_two_vector_magnitudes(data);
                write_data(vector_magnitudes, std::cout);
                std::string vector_mag_file = "vector_magnitudes.txt";
                save_to_file(vector_magnitudes, output_directory + vector_mag_file);
                break;
            } 
            
            case 3: {
                std::cout << "Requested task: 3" << std::endl;
                least_squares_fit(input_file,gradient,intercept,output_directory+"least_squares_fit.txt");
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
                save_to_file(x_pow_ys, output_directory + x_exp_y_file);
                break;
            }
            
            default : {
                std::cout << "Unrecognised task number: " << user_choice << std::endl;
            }
        
        }
    }

    return 0;

}