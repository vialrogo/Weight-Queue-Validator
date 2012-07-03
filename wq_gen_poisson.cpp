#include "wq_gen_poisson.h"

WQ_Gen_Poisson::WQ_Gen_Poisson(QObject *parent) :
    WQ_Generator(parent)
{
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
    short* datosGenerados = new short[60000000];
    for (int i = 0; i < 60000000; i++) datosGenerados[i] = 0;

    double numero = 0.0;
    numero -= log(generarNumeroAleatorio())/parametro;  /// <- Estoy seguro que esto es un logaritmo natural?????????? tiene que ser!!!

    while(numero<60000000)
    {
        datosGenerados[(int)numero]++;
        numero -= log(generarNumeroAleatorio())/parametro;
    }

    emit datosGeneradosExitosamente("Poisson with λ="+QString::number(parametro),datosGenerados);
}
