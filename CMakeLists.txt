# linux cmake -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -Bbuild
# -H.  -DCMAKE_EXPORT_COMPILE_COMMANDS=1

# windows cmake -H. -G "Visual Studio 16 2019" -DCMAKE_EXPORT_COMPILE_COMMANDS=1
# -Bbuild

cmake_minimum_required(VERSION 3.16)
project(img-cipher LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_CXX_FLAGS "-Os")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(image-cipher src/main.cpp src/image_cipher.cpp src/logistic_chaotic_map.cpp)
