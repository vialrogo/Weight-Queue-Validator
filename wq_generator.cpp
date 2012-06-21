#include "wq_generator.h"

WQ_Generator::WQ_Generator(QObject *parent) :
    QObject(parent)
{
}

WQ_Generator::~WQ_Generator()
{
}

double WQ_Generator::generarNumeroAleatorio()
{
    QTime midnight(0, 0, 0);
    double semilla = midnight.secsTo(QTime::currentTime());
//    double semilla = 1.0;
    double a = 16807;
    double m = 2147483647;

    semilla =  fmod((a * semilla), m);
    return (double) (semilla/m);
}
