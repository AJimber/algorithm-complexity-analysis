// AJimber
// algorithm-complexity-analysis


#include "../include/burbuja.hpp"
#include "../include/compartido.hpp"

void rellenarVector(std::vector<int> &v); 
void burbuja(std::vector<int> &v);
void tiemposOrdenacionBurbuja(int nMin, int nMax, int inc, int rep, 
    std::vector <double> &tiemposReales, std::vector<double> &numeroElementos);
void ajustePolinomico(const std::vector<double> &n, const std::vector<double> &tiemposReales, std::vector<double> &a, int gradoPolinomio);
void calcularTiemposEstimadosPolinomico(const std::vector<double> &numeroElementos, const std::vector<double> &a,
     std::vector<double> &tiemposEstimados); 



void rellenarVector(std::vector<int> &v)
{
    for(int i = 0; i < v.size(); i++)
    {
        v[i] = rand() % 10000000;
    }
}


void burbuja(std::vector<int> &v)
{
    int aux;
    for(int i = 0; i < v.size() - 1; i++)
    {
        for(int n = 0; n < v.size() - i - 1; n++)
        {
            if(v[n] > v[n + 1])
            {
                aux = v[n + 1];
                v[n + 1] = v[n];
                v[n] = aux;
            }    
        }
    }
}


void ordenacionBurbuja()
{
    srand((unsigned)time(0)); 
    int nMin, nMax, inc, rep;
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

    std::cout << "Introduzca el número de repeticiones: " << std::endl;
    std::cin >> rep;

    while(rep <= 0)
    {
        std::cout << "Las repeticiones deben ser mayores que 0: ";
        std::cin >> rep;
    }

    tiemposOrdenacionBurbuja(nMin, nMax, inc, rep, tiemposReales, numeroElementos);

 	std::vector<double> a;
    ajustePolinomico(numeroElementos, tiemposReales, a, 2);

    std::cout << "t(n) = " << a[0] << " + " << a[1] << "*n + " 
        << a[2] << "*n^2" << std::endl;

	std::vector<double> tiemposEstimados = std::vector<double>(tiemposReales.size());
    calcularTiemposEstimadosPolinomico(numeroElementos, a, tiemposEstimados);

    double coeficienteDeterminacion = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);

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


void tiemposOrdenacionBurbuja(int nMin, int nMax, int inc, int rep, 
    std::vector <double> &tiemposReales, std::vector<double> &numeroElementos)
{

    std::vector<int> v;
    v.resize(nMin);
    Clock time;
	double med = 0;
	float percentage = 0;

    for(size_t i = 0; i < rep; i++)
    {
        // Rellenar vector
        rellenarVector(v);
        time.start();
        // Ordenar
        burbuja(v);
        // Parar tiempo
        time.stop();
        // Tiempo medio de ordenación del vector
		med += time.elapsed();
        //
    }
    med = med / rep;
    tiemposReales.push_back(med);
    numeroElementos.push_back(nMin);

    percentage = (float)(nMin * 100) / nMax;

    std::cout << "Cargando: " << percentage << "%"
            << " | n = " << nMin
            << " | Tiempo medio: " << med << " microsegundos"
            << std::endl;

    for(int aux = nMin + inc; aux <= nMax; aux += inc)
    {
        med = 0;
        v.resize(aux);

        for(int n = 0; n < rep; n++)
        {
            rellenarVector(v);

            time.start();
            burbuja(v);
            time.stop();

            med += time.elapsed();
        }

        med = med / rep;

        numeroElementos.push_back(aux);
        tiemposReales.push_back(med);

        percentage = (float)(aux * 100) / nMax;

        std::cout << "Cargando: " << percentage << "%"
                << " | n = " << aux
                << " | Tiempo medio: " << med << " microsegundos"
                << std::endl;
    }
}





void ajustePolinomico(const std::vector<double> &n, const std::vector<double> &tiemposReales,
     std::vector<double> &a, int gradoPolinomio)
{
	int coef = gradoPolinomio + 1;
    a.resize(coef);

    std::vector<std::vector<double>> A(coef, std::vector<double>(coef));
    std::vector<std::vector<double>> B(coef, std::vector<double>(1));
    calcularMatrices(n, tiemposReales, coef, A, B);

    std::vector<std::vector<double>> x(coef, std::vector<double>(1));
    resolverSistemaEcuaciones(A, B, A.size(), x);

    for (int i = 0; i < x.size(); i++) {
        a[i] = x[i][0];
    }
}



void calcularTiemposEstimadosPolinomico(const std::vector<double> &numeroElementos, const std::vector<double> &a,
     std::vector<double> &tiemposEstimados)
{
	for (size_t i = 0; i < numeroElementos.size(); i++) 
	{
        tiemposEstimados[i] = calcularTiempoEstimadoPolinomico(numeroElementos[i], a);
    }
}

double calcularTiempoEstimadoPolinomico(const double &n, const std::vector<double> &a)
{
	double result = 0;
    for(size_t i = 0; i < a.size(); i++)
    {
        result += a[i] * pow(n, i);
    }
    return result;
}

