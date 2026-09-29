// AJimber
// algorithm-complexity-analysis


#include "../include/matriz.hpp"


void tiemposMatriz(int nMin, int nMax, int inc,
     std::vector<double> &tiemposReales, std::vector<double> &numeroElementos);
void cuadrado(const std::vector<std::vector<double>> &m,
    std::vector<std::vector<double>> &resultado);
void ajustePolinomicoMatriz(const std::vector<double> &n, const std::vector<double> &tiemposReales,
     std::vector<double> &a, int gradoPolinomio);


void rellenarMatriz(std::vector<std::vector<double>> &m, int row, int col)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            m[i][j] = 0.95 + 0.1 * ((double)rand() / RAND_MAX);
        }
    }
}



void matrizCuadrado()
{
    srand((unsigned)time(0)); 
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


    tiemposMatriz(nMin, nMax, inc, tiemposReales, numeroElementos);

 	std::vector<double> a;
    ajustePolinomicoMatriz(numeroElementos, tiemposReales, a, 3);

    std::cout << "t(n) = " << a[0] << " + " << a[1] << "*n + "
          << a[2] << "*n^2 + " << a[3] << "*n^3" << std::endl;

	std::vector<double> tiemposEstimados = std::vector<double>(tiemposReales.size());
    calcularTiemposEstimadosPolinomico(numeroElementos, a, tiemposEstimados);

    double coeficienteDeterminacion = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);

    std::ofstream plotOutFile("datosFinales.txt");
    if (!plotOutFile) {
        std::cerr << "ERROR: No se pudo crear el fichero datosFinales.txt" << std::endl;
        return;
    }
    else {
        for (size_t i = 0; i < tiemposReales.size(); i++) {
            plotOutFile << numeroElementos[i] << " " << tiemposReales[i] << " " << tiemposEstimados[i] << std::endl;
        }

        plotOutFile.close();
    }

    std::cout << "Coeficiente determinacion: " << coeficienteDeterminacion << std::endl;
    double n;
    do
    {
        std::cout << "Introduzca la cantidad de elementos (0 para salir): ";
        std::cin >> n;
        if(n != 0)
        {
            double tiempo = calcularTiempoEstimadoPolinomico(n, a);

            // Pasamos de microsegundos a segundos
            long long segundos = static_cast<long long>(tiempo / 1000000.0);
            long long anios = segundos / (365LL * 24 * 60 * 60);
            segundos %= (365LL * 24 * 60 * 60);
            long long dias = segundos / (24 * 60 * 60);
            segundos %= (24 * 60 * 60);
            long long minutos = segundos / 60;
            segundos %= 60;
            std::cout << "Tiempo estimado: " << anios << " anios, " << dias << " dias, "
                << minutos << " minutos y " << segundos << " segundos."<< std::endl;
        }

    } while(n != 0);
}


void cuadrado(const std::vector<std::vector<double>> &m, std::vector<std::vector<double>> &resultado)
{
    int n = m.size();

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            resultado[i][j] = 0;
            for(int k = 0; k < n; k++)
            {
                resultado[i][j] += m[i][k] * m[k][j];
            }
        }
    }
}


void tiemposMatriz(int nMin, int nMax, int inc,
    std::vector<double> &tiemposReales,
    std::vector<double> &numeroElementos)
{
    Clock time;

    for(int n = nMin; n <= nMax; n += inc)
    {
        std::vector<std::vector<double>> m(
            n, std::vector<double>(n));

        std::vector<std::vector<double>> resultado(
            n, std::vector<double>(n));

        rellenarMatriz(m, n, n);

        time.start();
        cuadrado(m, resultado);
        time.stop();

        double tiempo = time.elapsed();

        tiemposReales.push_back(tiempo);
        numeroElementos.push_back(n);

        float percentage = (float)n * 100 / nMax;

        std::cout << "Cargando: " << percentage << "%" << " | n = " << n
            << " | Tiempo: " << tiempo << " microsegundos" << std::endl;
    }
}



void ajustePolinomicoMatriz(const std::vector<double> &n, const std::vector<double> &tiemposReales,
     std::vector<double> &a, int gradoPolinomio)
{
	int coef = gradoPolinomio + 1;
    a.resize(coef);

    std::vector<std::vector<double>> A(coef, std::vector<double>(coef));
    std::vector<std::vector<double>> B(coef, std::vector<double>(1));
    calcularMatrices(n, tiemposReales, coef, A, B);

    std::vector<std::vector<double>> x(coef, std::vector<double>(1));
    resolverSistemaEcuaciones(A, B, A.size(), x);

    for (size_t i = 0; i < x.size(); i++) {
        a[i] = x[i][0];
    }
}

