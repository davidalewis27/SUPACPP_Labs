#include <iostream>
#include <vector>
#include <string>
#include <fstream>


int main()
{
    std::string input_file = "input2D_float.txt";
    std::ifstream data_file;
    std::string line;
    std::vector<float> x_data;
    std::vector<float> y_data;
    int N;
    std::string user_input;
    std::string xi;
    std::string yi;

    // Open the file
    data_file.open(input_file);


    // Check the file is correctly opened
    // Otherwise, exit programme and return -1 as error code
    if (!data_file.is_open()) {
        std::cout << "Error in opening file: " << input_file << std::endl;
        return -1;
    }
    else {
        std::cout << "File: " << input_file << " opened successfully" << std::endl;
    }

    // read first line, assume this is header
    std::getline(data_file, line);

    while (data_file >> xi >> yi) {         // xi, yi are strings
        x_data.push_back(std::stof(xi));
        y_data.push_back(std::stof(yi));
}

    // Request user to give number of lines to read
    std::cout << "Please enter the number of lines to be printed" << std::endl;


    // Close the file
    data_file.close();

    std::cout << "File: " << input_file << " closed" << std::endl;


    std::cin >> user_input;
    N = std::stoi(user_input);
    std::cout << "Requested " << N << " lines to be printed" << std::endl;

    for (int i=0; i<N; i++){
        std::cout << x_data[i] << " " << y_data[i] << std::endl;
    }

    return 0;

}