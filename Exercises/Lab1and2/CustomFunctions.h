#pragma once
#include <iostream>  // I/O
#include <vector>    // Vectors
#include <string>    // Strings
#include <utility>   // To use std::pair
#include <fstream>   //
#include <cmath>     //
#include <stdexcept> // Handle exceptions

bool read_2D_coords_from_file(const std::string& file, 
                              std::vector<std::pair<double, double>>& data);
                              
void get_number_of_lines(int& N);


// Fallback: anything std::ostream knows how to print
template <typename T>
void print_item(std::ostream& out, const T& x) {
    out << x;
}

// Overload for pairs, since std::ostream can't print a std::pair
template <typename A, typename B>
void print_item(std::ostream& out, const std::pair<A, B>& p) {
    out << p.first << " " << p.second;
}

template <typename Container>
void write_data(const Container& data, std::ostream& out, int N = -1) {
    int count = 0;
    for (const auto& item : data) {
        if (N >= 0 && count++ >= N) break;
        print_item(out, item);
        out << "\n";
    }
}


double two_component_vector_magitude(double x, double y);

int least_squares_fit(const std::string& data_file, 
                      double& gradient, 
                      double& intercept, 
                      const std::string& output_file = "least_squares_fit.txt", 
                      const std::string& error_file = "");

void get_user_choice(int& user_choice);

double chi_squared(const std::vector<double>& obs, 
                   const std::vector<double>& expected, 
                   const std::vector<double>& errors);

double linear(double x, double p, double q);


template <typename T>
T recursive_self_multiply(T x, T y) {
    long n = std::lround(y);                       // round y to nearest whole number

    if (n == 0) return T(1);                       // base case: x^0 = 1
    if (n < 0)  return T(1) / recursive_self_multiply(x, T(-n));   // x^-n = 1 / x^n

    double half = recursive_self_multiply(x, T(n / 2)); // x^(n/2)

    if (n % 2 == 0) {
        return half * half;                        // n even: (x^(n/2))^2
    } else {
        return half * half * x;                    // n odd:  (x^(n/2))^2 * x
    }
}