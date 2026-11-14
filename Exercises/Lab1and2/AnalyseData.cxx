#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "CustomFunctions.h"

int main()
{
    std::string input_file = "input2D_float.txt";
    int N_points;
    int i;
    double mag;
    double x;
    double y;
    std::vector<std::pair<double, double>> data;
    std::vector<double> vector_magnitudes;


    if (!read_2D_coords_from_file(input_file, data)) {
        return -1;
    }

    write_data_to_terminal(data);
    
    N_points = data.size();
    
    for (int i=0; i<N_points; i++){
        x = data[i].first;
        y = data[i].second;
        mag = two_component_vector_magitude(x,y);
        std::cout << "vec = (" << x << "," << y << ") --> magnitude = " << mag << std::endl;
        vector_magnitudes.push_back(mag);
    }

    return 0;

}