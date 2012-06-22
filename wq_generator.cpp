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
    //Sacar de aquí!!!
    semilla = time(NULL);
    a = 16807;
    m = 2147483647;

    semilla =  fmod((a * semilla), m);
    return (double) (semilla/m);
}
