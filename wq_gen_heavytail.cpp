#include "wq_gen_heavytail.h"

WQ_Gen_HeavyTail::WQ_Gen_HeavyTail(QObject *parent) :
    WQ_Generator(parent)
{
}

WQ_Gen_HeavyTail::~WQ_Gen_HeavyTail()
{
}

short* WQ_Gen_HeavyTail::generarDatosSinteticos(double parametro)
{
    short* arreglo = new short[60000000];
    return arreglo;
}
