#include "wq_gen_heavytail.h"

WQ_Gen_HeavyTail::WQ_Gen_HeavyTail(QObject *parent) :
    WQ_Generator(parent)
{
}

WQ_Gen_HeavyTail::~WQ_Gen_HeavyTail()
{
}

void WQ_Gen_HeavyTail::generarDatosSinteticos(double parametro_in, double alfa_in, int truncamiento_in)
{
    //En esta clase, parametro corresponde a beta
    parametro=parametro_in;
    alfa = alfa_in;
    truncamientoFuncion=truncamiento_in;
    start();
}

void WQ_Gen_HeavyTail::run()
{
    short* datosGenerados = new short[60000000];
    for (int i = 0; i < 60000000; i++) datosGenerados[i] = 0;

    QVector<int>* vector = new QVector<int>();
    double probabilidad=0.0;
    double time=0.0;
    double escalaExactitud=1000.0; //Arbitrario para cuestiones de pintar mejor

    for (int i = 1; i < truncamientoFuncion*escalaExactitud; ++i)
    {
        time = ((double)i)/escalaExactitud;
        probabilidad= (alfa*escalaExactitud)/(pow(time, parametro));

        for (int j = 0; j < probabilidad; ++j) vector->append( (int)time);
    }

    double tamano = (double)vector->size();
    int numero = vector->at((int)(generarNumeroAleatorio()*tamano));

    while(numero<60000000)
    {
        datosGenerados[numero]++;
        numero += vector->at((int)(generarNumeroAleatorio()*tamano));
    }

    emit datosGeneradosExitosamente("Heavy-Tail with β="+QString::number(parametro),datosGenerados);
}
