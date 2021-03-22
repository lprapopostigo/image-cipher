#include "image_cipher.hpp"
#include <cmath>
#include <iostream>

// genera una secuencia pseudo aleatoria de enteros, cuyos valores se encuentran
// en [0, 254)
std::vector<unsigned int> generate_key_sequence(unsigned int size, double x_0,
                                                double lambda) {
  logistic_chaotic_map map{x_0, lambda};
  std::vector<unsigned int> sequence{};
  sequence.resize(size);
  for (unsigned int i{0}; i < size; ++i) {
    sequence[i] = static_cast<int>(0x100 * map(i));
  }
  return std::move(sequence);
}

std::vector<unsigned int> create_vector_from_image(image const& img) {
  std::vector<unsigned int> tmp{};
  tmp.resize(img.height * img.width * 3);
  for (unsigned int i{0}; i < tmp.size(); ++i) {
    tmp[i] = img.data[i];
  }
  return std::move(tmp);
}

// wrapper para stbi_load, carga la imagen en la memoria y returna la estructura
// image correspondiente
image load_image(char const* filename) {
  image tmp{};
  tmp.data = stbi_load(filename, &tmp.width, &tmp.height, &tmp.channels, 3);
  if (tmp.data == nullptr) {
    throw std::runtime_error{"unable to load the image"};
  }
  return tmp;
};

// guarda la imagen
void write_image(char const* filename, image const& img) {
  stbi_write_png(filename, img.width, img.height, 3, img.data, img.width * 3);
}

// carga la llave, genera x_0 y lambda y a partir de ello genera el vector llave
std::vector<unsigned int> create_vector_from_key(char const* filename,
                                                 int size) {
  std::ifstream key_file{filename};
  std::string key{};
  std::getline(key_file, key);
  auto x_0{generate_seed(key)};
  return std::move(generate_key_sequence(size, x_0, 4));
}

// almacena los pixeles de un vector dado en una estructura image dada (para
// cada pixel del vector se realiza la conversion a rgb)
void vector_to_raw_data(std::vector<unsigned int> const& img_vector,
                        image const& img) {

  for (unsigned int i{0}; i < img_vector.size(); ++i) {
    img.data[i] = img_vector[i];
  }
}

// dado un string genera x_0 y lambda usando los 10 primeros caracteres
double generate_seed(std::string key) {
  // double lambda{0};
  std::bitset<40> even_bits{};
  std::bitset<40> odd_bits{};
  for (int i{0}; i < 10; ++i) {
    std::bitset<8> bitform_key{static_cast<unsigned long long>(key[i])};
    // lambda += static_cast<double>(key[i]);
    for (int k{0}; k < 8; k += 2) {
      even_bits[i * 8 + k] = bitform_key[k];
      even_bits[i * 8 + k + 1] = bitform_key[k + 1];
    }
  }
  // lambda = (lambda / 0x1'000'00) + 3.999'999'999'767'17; //
  // (5^x(2^(x+2)-1))/10^x; x= 32

  double seed{static_cast<double>(even_bits.to_ulong() + odd_bits.to_ulong())};
  seed /= 0x10'000'000'000; // 2^40
  double tmp{};
  seed = std::modf(seed, &tmp);
  if (seed == 0) {
    seed += 0.5;
  }
  return seed;
}
