#include "../include/sistemaEcuaciones.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>

namespace
{
constexpr double EPSILON = 1e-12;

void intercambiarFilas(std::vector<std::vector<double>> &matriz,
                       int fila1, int fila2)
{
    if (fila1 != fila2)
    {
        std::swap(matriz[fila1], matriz[fila2]);
    }
}

int buscarPivote(const std::vector<std::vector<double>> &matriz,
                 int columna, int inicio)
{
    int pivote = inicio;

    for (int i = inicio + 1; i < static_cast<int>(matriz.size()); ++i)
    {
        if (std::fabs(matriz[i][columna]) >
            std::fabs(matriz[pivote][columna]))
        {
            pivote = i;
        }
    }

    return pivote;
}
}

void resolverSistemaEcuaciones(
    std::vector<std::vector<double>> A,
    std::vector<std::vector<double>> B,
    int n,
    std::vector<std::vector<double>> &X)
{
    if (n <= 0 ||
        static_cast<int>(A.size()) != n ||
        static_cast<int>(B.size()) != n)
    {
        throw std::invalid_argument("Dimensiones incorrectas");
    }

    const int columnasB = static_cast<int>(B[0].size());

    for (int k = 0; k < n; ++k)
    {
        const int pivote = buscarPivote(A, k, k);

        if (std::fabs(A[pivote][k]) < EPSILON)
        {
            throw std::runtime_error("Sistema singular");
        }

        intercambiarFilas(A, k, pivote);
        intercambiarFilas(B, k, pivote);

        for (int i = k + 1; i < n; ++i)
        {
            const double factor = A[i][k] / A[k][k];

            for (int j = k; j < n; ++j)
            {
                A[i][j] -= factor * A[k][j];
            }

            for (int j = 0; j < columnasB; ++j)
            {
                B[i][j] -= factor * B[k][j];
            }
        }
    }

    X.assign(n, std::vector<double>(columnasB, 0.0));

    for (int columna = 0; columna < columnasB; ++columna)
    {
        for (int i = n - 1; i >= 0; --i)
        {
            double valor = B[i][columna];

            for (int j = i + 1; j < n; ++j)
            {
                valor -= A[i][j] * X[j][columna];
            }

            if (std::fabs(A[i][i]) < EPSILON)
            {
                throw std::runtime_error("Sistema singular");
            }

            X[i][columna] = valor / A[i][i];
        }
    }
}

double determinante(std::vector<std::vector<double>> &A)
{
    const int n = static_cast<int>(A.size());

    if (n == 0)
    {
        return 1.0;
    }

    std::vector<std::vector<double>> matriz = A;

    double det = 1.0;
    int signo = 1;

    for (int k = 0; k < n; ++k)
    {
        const int pivote = buscarPivote(matriz, k, k);

        if (std::fabs(matriz[pivote][k]) < EPSILON)
        {
            return 0.0;
        }

        if (pivote != k)
        {
            intercambiarFilas(matriz, pivote, k);
            signo = -signo;
        }

        const double valorPivote = matriz[k][k];
        det *= valorPivote;

        for (int i = k + 1; i < n; ++i)
        {
            const double factor = matriz[i][k] / valorPivote;

            for (int j = k + 1; j < n; ++j)
            {
                matriz[i][j] -= factor * matriz[k][j];
            }
        }
    }

    return signo * det;
}