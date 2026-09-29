// AJimber
// algorithm-complexity-analysis

#ifndef COMPARTIDO_HPP
#define COMPARTIDO_HPP

#include <vector>
#include <cmath>

void rellenaMatAleatoria(
    std::vector<std::vector<double>> &m,
    int ordenmat);

double sumatorio(
    const std::vector<double> &n,
    const std::vector<double> &t,
    int expN,
    int expT);

double calcularCoeficienteDeterminacion(
    const std::vector<double> &tiemposReales,
    const std::vector<double> &tiemposEstimados);

void calcularMatrices(
    const std::vector<double> &numeroElementos,
    const std::vector<double> &tiemposReales,
    int ordenMatrizSistema,
    std::vector<std::vector<double>> &matrizCoeficientes,
    std::vector<std::vector<double>> &matrizTerminosIndependientes);

#endif