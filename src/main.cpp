// AJimber
// algorithm-complexity-analysis

#include <iostream>
#include "../include/burbuja.hpp"
#include "../include/fibonacci.hpp"
#include "../include/matriz.hpp"
#include "../src/ClaseTiempo.cpp"

int main()
{
    int opcion;

    do
    {
        std::cout << "\n========== MENU ==========\n";
        std::cout << "1. Ordenacion Burbuja\n";
        std::cout << "2. Fibonacci Recursivo\n";
        std::cout << "3. Cuadrado de una matriz\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch(opcion)
        {
            case 1:
                ordenacionBurbuja();
                break;

            case 2:
                fibonacciRecursivo();
                break;

            case 3:
                matrizCuadrado();
                break;
            case 0:
                std::cout << "Fin del programa." << std::endl;
                break;

            default:
                std::cout << "Opcion incorrecta." << std::endl;
                break;
        }
    } while(opcion != 0);

    return 0;
}