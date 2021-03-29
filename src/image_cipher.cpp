#include "image_cipher.hpp"

// genera una secuencia pseudo aleatoria de enteros, cuyos valores se encuentran
// en [0, 254)
std::vector<uint8_t> generate_key_sequence(unsigned int size, double x_0,
                                           double lambda) {
  logistic_chaotic_map map{x_0, lambda};
  std::vector<uint8_t> sequence{};
  sequence.resize(size);
  for (unsigned int i{0}; i < size; ++i) {
    sequence[i] = static_cast<uint8_t>(0x100 * map(i));
  }
  return std::move(sequence);
}

std::vector<uint8_t> create_vector_from_image(image const& img) {
  std::vector<uint8_t> tmp{};
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
  return tmp;
};

// guarda la imagen
int write_image(char const* filename, image const& img) {
  return stbi_write_png(filename, img.width, img.height, 3, img.data,
                        img.width * 3);
}

// carga la llave, genera x_0 y lambda y a partir de ello genera el vector llave
std::vector<uint8_t> create_vector_from_key(char const* key, int size) {
  auto x_0{generate_seed(key)};
  return std::move(generate_key_sequence(size, x_0, 4));
}

// almacena los pixeles de un vector dado en una estructura image dada (para
// cada pixel del vector se realiza la conversion a rgb)
void vector_to_raw_data(std::vector<uint8_t> const& img_vector,
                        image const& img) {

  for (unsigned int i{0}; i < img_vector.size(); ++i) {
    img.data[i] = img_vector[i];
  }
}

// given a key, generate x_0
double generate_seed(char const* key) {
  // double lambda{0};
  std::bitset<40> even_bits{};
  std::bitset<40> odd_bits{};
  for (uint8_t i{0}; i < 10; ++i) {
    std::bitset<8> bitform_key{static_cast<unsigned long>(key[i])};
    // lambda += static_cast<double>(key[i]);
    for (uint8_t k{0}; k < 4; ++k) {
      even_bits[k] = bitform_key[i * 4 + k];
      odd_bits[k] = bitform_key[i * 4 + k + 1];
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

uint8_t char_number(char const* ch_ptr) {
  uint8_t counter{0};
  while (ch_ptr[counter] != '\0') {
    ++counter;
  }
  return counter;
}