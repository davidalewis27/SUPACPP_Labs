#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <stdexcept>

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


// Print indvidual data types to the terminal
// Print vector of pairs of doubles
void print_item(const std::pair<double, double>& p) {
    std::cout << p.first << " " << p.second << "\n";
}

// Print double
void print_item(double x) {
    std::cout << x << "\n";
}

// Print string
void print_item(const std::string& s) {
    std::cout << s << "\n";
}

template <typename T>
void print_item(const std::vector<T>& v, int& N) {
    for (int i = 0; i < N; ++i) {
        print_item(v[i]);               // picks the right overload for T
    }
}


void get_number_of_lines(int& N) {
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
    
}

// Refactored to print N lines from a vector
template <typename Container>
void write_data_to_terminal(const Container& data, int& N) {
    print_item(data, N);

}

template void write_data_to_terminal<std::vector<std::pair<double, double>>>(const std::vector<std::pair<double, double>>&, int& N);
template void write_data_to_terminal<std::vector<double>>(const std::vector<double>&, int& N);
template void write_data_to_terminal<std::vector<int>>(const std::vector<int>&, int& N);
template void write_data_to_terminal<std::vector<std::string>>(const std::vector<std::string>&, int& N);


// Computed the magnitude of a vector
// assuming(x,y) is position from (0,0)
double two_component_vector_magitude(double x, double y) {
    double vector_magnitude;
    vector_magnitude = std::sqrt(x*x + y*y);
    return vector_magnitude;
}


double chi_squared(std::vector<double> obs, std::vector<double> expected, std::vector<double> errors){

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
                      const std::string& error_file = ""
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
    if (denom < 1e-6) {
        std::cout << "WARN: least_squares_fit denominator small (<1e-6), check result carefully \n" << std::endl;
    }
    
    gradient = ( N*sum_xy - sum_x*sum_y ) / denom;
    intercept = ( sum_sq_x*sum_y - sum_xy*sum_x ) / denom;
    
    std::cout << "Least squares fit: y = " << gradient << " x + " << intercept << "\n" << std::endl;  
    
    std::string out_file="least_squares_fit.txt";
    std::ofstream out_stream;
    // Open the file
    out_stream.open(out_file);


    // Check the file is correctly opened
    // Otherwise, return false to be caught back in main
    if (!out_stream.is_open()) {
        std::cout << "Error in opening file: " << out_file << std::endl;
    }
    else {
        std::cout << "File: " << out_file << " opened successfully" << std::endl;
    }
    out_stream << "y = " << gradient << " x + " << intercept << "\n" << std::endl;
    out_stream.close();
     
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
        
        // Compute the expected value from the least squares fit
        for (int i = 0; i < data.size(); ++i) {
            const double x = data[i].first;
            const double y = data[i].second;
            
            model_i = linear(x,gradient,intercept);
            
            ys.push_back(y);
            model.push_back(model_i);
            yerrs.push_back(data_err[i].second);
            
        }
        
        chi_sq = chi_squared(ys, model, yerrs);
    
        std::cout << "chi-squared = " << chi_sq << std::endl;
        
        // Check more than 2 data points, if not, do not computed reduced chi-sq
        if (N <= 2) {
            std::cout << "Less than two data points provided, not computing chi^2/NDOF" << std::endl;
        }
        else {
            double NDOF;
            NDOF = N - 2.0; // DOF = N data points - 2 fit parameters
            std::cout << "NDOF = " << N << " - 2 = " << NDOF  << std::endl;
            std::cout << "chi-squared/NDOF = " << chi_sq/NDOF << std::endl;
        }
    }
    
    
    return 0;

}

void get_user_choice(int& user_choice) {

    std::string user_input;
    std::cout << "Which task would you like to perform?" << std::endl;
    std::cout << "1 - Print N lines of data" << std::endl;
    std::cout << "2 - Print magnitude of all data points" << std::endl;
    std::cout << "3 - Least squares fit" << std::endl;
    std::cout << "4 - Least squares fit with chi-squared" << std::endl;
    std::cout << "5 - Compute x^y from data with recursion" << std::endl;
    std::cin >> user_input;
    user_choice = std::stoi(user_input);
    
}


template <typename T>
T recursive_self_multiply(T x, T y) {
    long n = std::lround(y);                                // round y to nearest whole number
    if (n == 0) return 1;                                   // base case: x^0 = 1
    if (n < 0)  return 1 / recursive_self_multiply(x, T(-n));  // negative exponent
    return x * recursive_self_multiply(x, T(n - 1));        // x^n = x * x^(n-1)
}

// explicit instantiations
template double recursive_self_multiply<double>(double, double);
template float  recursive_self_multiply<float>(float, float);
template int  recursive_self_multiply<int>(int, int);
