#include "wq_generator.h"

WQ_Generator::WQ_Generator(QObject *parent) :
    QThread(parent)
{
    semilla = time(NULL);
    a = 16807;
    m = 2147483647;
}

WQ_Generator::~WQ_Generator()
{
}

double WQ_Generator::generarNumeroAleatorio()
{
    semilla =  fmod((a * semilla), m);
    return (double) (semilla/m);
}

void WQ_Generator::run(){}
