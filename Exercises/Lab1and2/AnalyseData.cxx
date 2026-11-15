#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "CustomFunctions.h"

int main()
{
    std::string input_file = "input2D_float.txt";
    std::string error_file = "error2D_float.txt";
    int user_choice;
    int N_points;
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
        write_data_to_terminal(data);
    
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
            std::cout << "vec = (" << x << "," << y << ") --> magnitude = " << mag << std::endl;
            vector_magnitudes.push_back(mag);
        }
    }
    else if(user_choice == 3) {
        std::cout << "Requested task: 3" << std::endl;
        least_squares_fit(input_file,gradient,intercept);
        std::cout << "Least squares fit: y = " << gradient << " x + " << intercept << std::endl;   
    }
    else if(user_choice == 4) {
        std::cout << "Requested task: 3" << std::endl;
        least_squares_fit(input_file,gradient,intercept,error_file);
    }
    else{
        std::cout << "Unrecognised task number: " << user_choice << std::endl;
    
    }


    return 0;

}