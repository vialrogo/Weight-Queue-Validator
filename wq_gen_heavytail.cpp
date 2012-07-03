#include "wq_gen_heavytail.h"

WQ_Gen_HeavyTail::WQ_Gen_HeavyTail(QObject *parent) :
    WQ_Generator(parent)
{
}

WQ_Gen_HeavyTail::~WQ_Gen_HeavyTail()
{
}

void WQ_Gen_HeavyTail::generarDatosSinteticos(double parametro_in)
{
    //En esta clase, parametro corresponde a beta
    parametro=parametro_in;
    start();
}

void WQ_Gen_HeavyTail::run()
{
    double alfa = 10.0; /// Arbitrario!!!

    short* datosGenerados = new short[60000000];
    for (int i = 0; i < 60000000; i++) datosGenerados[i] = 0;

    /// ***************************
    double numero = 0.0;
    numero += pow(alfa/generarNumeroAleatorio(), 1.0/parametro);
    qDebug("aleatorio: %f",generarNumeroAleatorio());

    while(numero<60000000)
    {
        datosGenerados[(int)numero]++;
        numero += pow(alfa/generarNumeroAleatorio(), 1.0/parametro);
//        qDebug("numero: %f",numero);
    }
    /// ***************************

    emit datosGeneradosExitosamente("Poisson with β="+QString::number(parametro),datosGenerados);
}
