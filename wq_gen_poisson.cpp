#include "wq_gen_poisson.h"

WQ_Gen_Poisson::WQ_Gen_Poisson(QObject *parent) :
    WQ_Generator(parent)
{
}

WQ_Gen_Poisson::~WQ_Gen_Poisson()
{
}

short* WQ_Gen_Poisson::generarDatosSinteticos(double parametro)
{
    //En esta clase, parametro corresponde a lambda
    short* arreglo = new short[60000000];
    for (int i = 0; i < 60000000; i++) arreglo[i] = 0;

    double numero = 0.0;
    numero += ((-1.0)/parametro)*log(generarNumeroAleatorio());

    int contador=0;
    while(numero<60000000)
    {
        contador++;
        arreglo[(int)numero]++;
        numero -= log(generarNumeroAleatorio())/parametro;

        if(contador==10000){ qDebug("numero: %f",numero); contador=0;}
    }

    return arreglo;
}
