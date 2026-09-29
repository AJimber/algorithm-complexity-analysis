// AJimber
// algorithm-complexity-analysis


#include "../include/fibonacci.hpp"


void tiemposOrdenacionFibonacci(int nMin, int nMax, int inc,
    std::vector<double> &tiemposReales, std::vector<double> &numeroElementos);
void ajusteExponencial(const std::vector <double> &numeroElementos, 
    const std::vector <double> &tiemposReales, std::vector <double> &a);
void calcularTiemposEstimadosExponencial(const std::vector<double>&numeroElementos,
    const std::vector<double> &a, std::vector<double>&tiemposEstimados);
double calcularTiempoEstimadoExponencial(const double &n, const std::vector<double> &a);
double sumatorio(const std::vector<double> &n, const std::vector<double> &t, int expN, int expT);
double calcularCoeficienteDeterminacion(const std::vector<double> &tiemposReales, const std::vector<double> &tiemposEstimados);
void calcularMatrices(const std::vector<double> &numeroElementos, const std::vector<double> &tiemposReales, int ordenMatrizSistema,
    std::vector<std::vector<double>> &matrizCoeficientes, std::vector<std::vector<double>> &matrizTerminosIndependientes);




long long fibonacci(int n)
{
    if (n == 0) 
        return 0;
    if (n == 1) 
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}


void fibonacciRecursivo()
{
    int nMin, nMax, inc;
    std::vector<double> tiemposReales;
    std::vector<double> numeroElementos;

    std::cout<<"Introduzca la cantidad minima de elementos: "<<std::endl;
    std::cin >> nMin;

    std::cout<<"Introduzca la cantidad máxima de elementos: "<<std::endl;
    std::cin >> nMax; 

	while(nMax<nMin)
    {
        std::cout<<"El termino maximo es menos que el minimo, introduzca otro valor para el termino maximo: ";
        std::cin>> nMax;
    }

    std::cout << "Introduzca el incremento: " << std::endl;
    std::cin >> inc;

    while(inc <= 0)
    {
        std::cout << "El incremento debe ser mayor que 0: ";
        std::cin >> inc;
    }

    tiemposOrdenacionFibonacci(nMin, nMax, inc, tiemposReales, numeroElementos);

    std::vector<double> a;
    ajusteExponencial(numeroElementos, tiemposReales, a);

    std::cout << "t(n) = " << a[0] << " + "
        << a[1] << "*2^n"  << std::endl;

    std::vector<double> tiemposEstimados;

    calcularTiemposEstimadosExponencial(numeroElementos, a, tiemposEstimados);

    double coeficiente = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);
    std::cout << "Coeficiente determinacion: " << coeficiente << std::endl;
    
    std::ofstream plotOutFile("datosFinales.txt");
    if (!plotOutFile) {
        std::cerr << "ERROR: No se pudo crear el fichero datosFinales.txt" << std::endl;
        return;
    }
    else {
        for (int i = 0; i < tiemposReales.size(); i++) {
            plotOutFile << numeroElementos[i] << " " << tiemposReales[i] << " " << tiemposEstimados[i] << std::endl;
        }

        plotOutFile.close();
    }

    double n;
    do
    {
        std::cout << "Introduzca la cantidad de elementos (0 para salir): ";
        std::cin >> n;
        if(n != 0)
        {
            double tiempo = calcularTiempoEstimadoExponencial(n, a);

            // Pasamos de microsegundos a segundos
            long long segundos = static_cast<long long>(tiempo / 1000000.0);
            long long anios = segundos / (365LL * 24 * 60 * 60);
            segundos %= (365LL * 24 * 60 * 60);
            long long dias = segundos / (24 * 60 * 60);
            segundos %= (24 * 60 * 60);
            long long minutos = segundos / 60;
            segundos %= 60;
            std::cout << "Tiempo estimado: " << anios << " anios, " << dias << " dias, "
                << minutos << " minutos y " << segundos << " segundos." << std::endl;
        }

    } while(n != 0);
}





void tiemposOrdenacionFibonacci(int nMin, int nMax, int inc,
    std::vector<double> &tiemposReales, std::vector<double> &numeroElementos)
{
    Clock time;

    for(int n = nMin; n <= nMax; n += inc)
    {
        time.start();
        fibonacci(n);
        time.stop();
        double tiempo = time.elapsed();

        tiemposReales.push_back(tiempo);
        numeroElementos.push_back(n);

        float percentage = (float)n * 100 / nMax;
        std::cout << "Cargando: " << percentage << "%" << " | n = " << n
            << " | Tiempo: " << tiempo << " microsegundos" << std::endl;
    }
}





void ajusteExponencial(const std::vector <double> &numeroElementos, 
    const std::vector <double> &tiemposReales, std::vector <double> &a)
{
    // Cambio de variable z = 2^n
    std::vector<double> z(numeroElementos.size());
    for(size_t i = 0; i < numeroElementos.size(); i++)
    {
        z[i] = pow(2.0, numeroElementos[i]);
    }

    // t = a0 + a1*z -> ajuste de grado 1
    int ordenMatrizSistema = 2;
    std::vector<std::vector<double>> matrizCoeficientes(ordenMatrizSistema,
        std::vector<double>(ordenMatrizSistema));
    std::vector<std::vector<double>> matrizTerminosIndependientes(
        ordenMatrizSistema, std::vector<double>(1));

    calcularMatrices(z, tiemposReales, ordenMatrizSistema,
        matrizCoeficientes, matrizTerminosIndependientes);
    std::vector<std::vector<double>> X(ordenMatrizSistema, std::vector<double>(1));
    resolverSistemaEcuaciones(matrizCoeficientes, matrizTerminosIndependientes,
        ordenMatrizSistema, X);

    a.resize(2);
    a[0] = X[0][0];
    a[1] = X[1][0];
}


void calcularTiemposEstimadosExponencial(const std::vector<double>&numeroElementos,
    const std::vector<double> &a, std::vector<double>&tiemposEstimados)
{
    tiemposEstimados.resize(numeroElementos.size());

	for (size_t i = 0; i < numeroElementos.size(); i++) 
	{
        tiemposEstimados[i] = calcularTiempoEstimadoExponencial(numeroElementos[i], a);
    }
}

double calcularTiempoEstimadoExponencial(const double &n, const std::vector<double> &a)
{
    return a[0] + a[1] * pow(2.0, n);
}

