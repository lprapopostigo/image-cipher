#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "image_cipher.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cout << "USAGE: image-cipher [inputFile] [keyFile] [outputFile]"
              << std::endl;
    return 0;
  }
  // Load img and create a std vector from it
  auto img{load_image(argv[1])};
  auto img_vector{create_vector_from_image(img)};

  // Load key and create a std vector from it
  auto key_vector{create_vector_from_key(argv[2], img.width * img.height * 3)};

  // xor operation between vectors
  for (unsigned int i{0}; i < img_vector.size(); ++i) {
    img_vector[i] ^= key_vector[i];
  }

  // Save img and free memory
  vector_to_raw_data(img_vector, img);
  write_image(argv[3], img);
  stbi_image_free(img.data);
}
