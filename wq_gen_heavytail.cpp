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
    double alfa = 100.0; /// Arbitrario!!!

    short* datosGenerados = new short[60000000];
    for (int i = 0; i < 60000000; i++) datosGenerados[i] = 0;

    /// ***************************
//    double a=0.0;
//    double b=0.0;
//    double real=0.0;
//    double numero=0.0;

//    while (numero<60000000)
//    {
//        a=generarNumeroAleatorio()*alfa;
//        b=generarNumeroAleatorio()*500; //Arbitrario

//        real = alfa/(pow(b,parametro));

//        if(a< real){
//            datosGenerados[(int)numero]++;
//            numero+=b;
//        }
//    }
    /// ***************************

    QVector<int>* vector = new QVector<int>();
    double probabilidad=0.0;

    for (int i = 1; i < 1000; ++i) {
        probabilidad= alfa/(pow(i,parametro));
        qDebug("probabilidad: %f",probabilidad);
        for (int j = 0; j < probabilidad; ++j) {
            vector->append(i);
        }
    }

    double tamano = (double)vector->size();

    qDebug("size: %d",tamano);

    emit datosGeneradosExitosamente("Heavy-Tail with β="+QString::number(parametro),datosGenerados);
}
