# AJimber
# algorithm-complexity-analysis

cmake_minimum_required(VERSION 3.10)

project(algorithm-complexity-analysis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(practica1
    main.cpp
    burbuja.cpp
    fibonacci.cpp
    matriz.cpp
    compartido.cpp
    sistemaEcuaciones.cpp
)

target_compile_options(main PRIVATE -Wall -Wextra)
