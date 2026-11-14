#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "CustomFunctions.h"

int main()
{
    std::string input_file = "input2D_float.txt";
    std::vector<std::pair<float, float>> data;


    if (!read_2D_coords_from_file(input_file, data)) {
        return -1;
    }

    write_data_to_terminal(data);

    return 0;

}