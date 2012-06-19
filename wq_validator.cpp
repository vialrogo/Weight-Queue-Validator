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
    double limiteGrafica = 1000000.0;

    QVector<QPointF>* vectorSalida = new QVector<QPointF>();
    int saltos = ceil( ((double)(fin-inicio)) / limiteGrafica);

    for (int i = inicio; i < fin; ++i) {
        vectorSalida->push_back(QPointF(i,vectorDatos.at(numDatos)[i]));
    }

    return vectorSalida;
}
