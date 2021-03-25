#pragma once
#include "logistic_chaotic_map.hpp"
#include "stb_image.h"
#include "stb_image_write.h"
#include <bitset>
#include <cmath>
#include <fstream>
#include <vector>

struct image {
  uint8_t* data{nullptr};
  int width{0};
  int height{0};
  int channels{0};
};

std::vector<unsigned int> generate_key_sequence(unsigned int size, double x_0,
                                                double lambda);
image load_image(char const* filename);
void write_image(char const* filename, image const& img);
std::vector<unsigned int> create_vector_from_image(image const& img);
std::vector<unsigned int> create_vector_from_key(char const* filename,
                                                 int size);
void vector_to_raw_data(std::vector<unsigned int> const& pixel_vector,
                        image const& img);
double generate_seed(std::string key);