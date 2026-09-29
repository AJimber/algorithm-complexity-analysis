// AJimber
// algorithm-complexity-analysis


#ifndef BURBUJA_HPP
#define BURBUJA_HPP

#include "../include/sistemaEcuaciones.hpp"
#include "../src/ClaseTiempo.cpp"

#include <limits>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include  <fstream>


void ordenacionBurbuja(); 

void ajustePolinomico(
    const std::vector<double> &n,
    const std::vector<double> &tiemposReales,
    std::vector<double> &a,
    int gradoPolinomio);

void calcularTiemposEstimadosPolinomico(
    const std::vector<double> &numeroElementos,
    const std::vector<double> &a,
    std::vector<double> &tiemposEstimados);

double calcularTiempoEstimadoPolinomico(
    const double &n,
    const std::vector<double> &a);



#endif