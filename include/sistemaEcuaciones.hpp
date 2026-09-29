#ifndef SISTEMA_ECUACIONES_HPP
#define SISTEMA_ECUACIONES_HPP

#include <vector>

void resolverSistemaEcuaciones(
    std::vector<std::vector<double>> A,
    std::vector<std::vector<double>> B,
    int n,
    std::vector<std::vector<double>> &X
);

double determinante(std::vector<std::vector<double>> &A);

#endif