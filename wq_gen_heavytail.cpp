#include "wq_gen_heavytail.h"

WQ_Gen_HeavyTail::WQ_Gen_HeavyTail(QObject *parent) :
    WQ_Generator(parent)
{
    datosGenerados = new short[60000000];
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
    for (int i = 0; i < 60000000; i++) datosGenerados[i] = 0;

    emit datosGeneradosExitosamente("Heavy-Tailed with β="+QString::number(parametro),datosGenerados);
}
