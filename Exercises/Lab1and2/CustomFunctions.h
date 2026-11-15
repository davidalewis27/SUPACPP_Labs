#pragma once

bool read_2D_coords_from_file(const std::string& file, 
                              std::vector<std::pair<double, double>>& data);

void write_data_to_terminal(const std::vector<std::pair<double, double>>& data);

double two_component_vector_magitude(double x, double y);

int least_squares_fit(const std::string& data_file, double& gradient, double& intercept, const std::string& error_file = "");

void get_user_choice(int& user_choice);

double chi_squared(std::vector<double> obs, std::vector<double> expected, std::vector<double> errors);

double linear(double x, double p, double q);

template <typename T>
T recursive_self_multiply(T x, T y);