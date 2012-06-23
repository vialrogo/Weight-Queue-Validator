#include "wq_gen_poisson.h"

WQ_Gen_Poisson::WQ_Gen_Poisson(QObject *parent) :
    WQ_Generator(parent)
{
    datosGenerados = new short[60000000];
}

WQ_Gen_Poisson::~WQ_Gen_Poisson()
{
}

void WQ_Gen_Poisson::generarDatosSinteticos(double parametro_in)
{
    //En esta clase, parametro corresponde a lambda
    parametro=parametro_in;
    start();
}

void WQ_Gen_Poisson::run()
{
    for (int i = 0; i < 60000000; i++) datosGenerados[i] = 0;

    double numero = 0.0;
    numero += ((-1.0)/parametro)*log(generarNumeroAleatorio());

    while(numero<60000000)
    {
        datosGenerados[(int)numero]++;
        numero -= log(generarNumeroAleatorio())/parametro;
    }

    emit datosGeneradosExitosamente("Poisson with λ="+QString::number(parametro),datosGenerados);
}
