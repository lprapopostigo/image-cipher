#pragma once
#include "logistic_chaotic_map.hpp"
#include "stb/stb_image.h"
#include "stb/stb_image_write.h"
#include <bitset>
#include <cmath>
#include <vector>

struct image {
  uint8_t* data{nullptr};
  int width{0};
  int height{0};
  int channels{0};
};

std::vector<uint8_t> generate_key_sequence(unsigned int size, double x_0,
                                           double lambda);
image load_image(char const* filename);
int write_image(char const* filename, image const& img);
std::vector<uint8_t> create_vector_from_image(image const& img);
std::vector<uint8_t> create_vector_from_key(char const* filename, int size);
void vector_to_raw_data(std::vector<uint8_t> const& pixel_vector,
                        image const& img);
double generate_seed(char const* key);

uint8_t char_number(char const* ch_ptr);