#include "wq_validator.h"

WQ_Validator::WQ_Validator()
{
}

WQ_Validator::~WQ_Validator()
{
}

void WQ_Validator::agregarDatos(short* datos)
{
    vectorDatos.push_back(datos);
}

void WQ_Validator::eliminarDatos(int numDato)
{
    vectorDatos.remove(numDato);
}

QVector<QPointF>* WQ_Validator::obtenerVectorDatos(int numDatos, int inicio, int fin)
{
    double limiteGrafica = 4000000.0; //Limite de puntos que puedo graficar sin que se muera

    QVector<QPointF>* vectorSalida = new QVector<QPointF>();
    int saltos = ceil( ((double)(fin-inicio)) / limiteGrafica);
    int contador=0;
    int acumulador=0;

    for (int i = inicio; i < fin; ++i)
    {
        contador++;
        acumulador+=vectorDatos.at(numDatos)[i];

        if(contador==saltos)
        {
            vectorSalida->push_back(QPointF(i-(saltos/2),acumulador));
            contador=0;
            acumulador=0;
        }
    }

    return vectorSalida;
}
