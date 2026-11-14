#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "CustomFunctions.h"

int main()
{
    std::string input_file = "input2D_float.txt";
    std::vector<std::pair<float, float>> data;
    int N;
    std::string user_input;

    if (!read_2D_coords_from_file(input_file, data)) {
        return -1;
    }

    // Request user to give number of lines to read
    std::cout << "Please enter the number of lines to be printed" << std::endl;


    std::cin >> user_input;
    N = std::stoi(user_input);
    std::cout << "Requested " << N << " lines to be printed" << std::endl;

    for (int i=0; i<N; i++){
        std::cout << data[i].first << " " << data[i].second << std::endl;
    }

    return 0;

}