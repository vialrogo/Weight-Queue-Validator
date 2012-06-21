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
    QTime midnight(0, 0, 0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    double limiteGrafica = 1000000.0; //Limite de puntos que puedo graficar sin que se muera
    QVector<QPointF>* vectorSalida = new QVector<QPointF>();
    int saltos = ceil( ((double)(fin-inicio)) / limiteGrafica);
    int aleatorio=0;

    for (int i = inicio; i < fin; i+=saltos)
    {
        aleatorio = qrand()%saltos;
        vectorSalida->push_back(QPointF(i+aleatorio,vectorDatos.at(numDatos)[i+aleatorio]));
    }

    return vectorSalida;
}
