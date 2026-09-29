// AJimber
// algorithm-complexity-analysis

#include "../include/compartido.hpp"
#include "../include/sistemaEcuaciones.hpp"

void rellenaMatAleatoria(std::vector<std::vector<double> > &m, int ordenmat) 
{
    srand(time(NULL));
    
    for(int i = 0; i < ordenmat; i++) 
    {
        for (int j = 0; j < ordenmat; j++) 
        {
            double aux = 0.95 + 0.1 * ((rand() % 100) / 99.0);
            m[i][j] = aux;
        }
    }
}



double sumatorio(const std::vector<double> &n, const std::vector<double> &t, int expN, int expT)
{
	double r = 0;
	for(size_t i = 0; i < n.size(); i++)
	{   
        //sumatorio general del polinomio
        r += (pow(n[i], expN) * pow(t[i], expT));
	}

	return r;
}



double calcularCoeficienteDeterminacion(const std::vector<double> &tiemposReales, const std::vector<double> &tiemposEstimados)
{
	//Calculamos las medias
	double mdEst = 0;
	double mdRl = 0;
   
	for (size_t i = 0; i < tiemposReales.size(); i++) 
	{
        mdEst += tiemposEstimados[i];
        mdRl  += tiemposReales[i];
    }
    
	mdEst /= tiemposReales.size();
	mdRl  /= tiemposReales.size();

    //Calculamos las varianzas
    double varEst = 0;
    double varRl = 0;

    for(size_t i = 0; i < tiemposReales.size(); i++) 
	{
        varRl  += pow((tiemposReales[i]-mdRl), 2);
    }

    for(size_t i = 0; i < tiemposEstimados.size(); i++) 
	{
        varEst += pow((tiemposEstimados[i]-mdEst), 2);
    }
    varEst = varEst / tiemposEstimados.size();
    varRl  = varRl / tiemposReales.size();

    return varEst / varRl;
}

void calcularMatrices(
    const std::vector<double> &numeroElementos,
    const std::vector<double> &tiemposReales,
    int ordenMatrizSistema,
    std::vector<std::vector<double>> &matrizCoeficientes,
    std::vector<std::vector<double>> &matrizTerminosIndependientes)
{
    for(int i = 0; i < ordenMatrizSistema; i++)
    {
        for(int j = 0; j < ordenMatrizSistema; j++)
        {
            matrizCoeficientes[i][j] = sumatorio(numeroElementos, tiemposReales, i + j, 0);
        }
    }

    for(int i = 0; i < ordenMatrizSistema; i++)
    {
        matrizTerminosIndependientes[i][0] = sumatorio(numeroElementos, tiemposReales, i, 1);
    }
}




