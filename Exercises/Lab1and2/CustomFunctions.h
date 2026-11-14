#pragma once

bool read_2D_coords_from_file(std::string& file, 
                              std::vector<std::pair<double, double>>& data);

void write_data_to_terminal(const std::vector<std::pair<double, double>>& data);

double two_component_vector_magitude(double x, double y);