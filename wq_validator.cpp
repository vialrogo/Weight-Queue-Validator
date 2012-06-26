#include "wq_validator.h"

WQ_Validator::WQ_Validator()
{
    vectorDatos = new QVector<short*>();
}

WQ_Validator::~WQ_Validator()
{
}

void WQ_Validator::agregarDatos(short* datos)
{
    vectorDatos->push_back(datos);
}

void WQ_Validator::eliminarDatos(int numDato)
{
    vectorDatos->remove(numDato);
}

QVector<QPointF>* WQ_Validator::obtenerVectorDatos(int numDatos, int tipoAnalisis, int inicio, int fin)
{
    QTime midnight(0, 0, 0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    double limiteGrafica = 1000000.0; //Limite de puntos que puedo graficar sin que se muera
    QVector<QPointF>* vectorSalida = new QVector<QPointF>();
    int saltos = ceil( ((double)(fin-inicio)) / limiteGrafica);
    int aleatorio=0;
    short* datosAnalisis;

    if(tipoAnalisis==0) datosAnalisis = analisisSeriesTiempo(numDatos);
    if(tipoAnalisis==1) datosAnalisis = analisisFuncionProbabilidad(numDatos);
    if(tipoAnalisis==2) datosAnalisis = analisisAutocorrelacionM(numDatos, 1 /* Ojo!! */);
    if(tipoAnalisis==3) datosAnalisis = analisisHvsM(numDatos);

    for (int i = inicio; i < fin; i+=saltos)
    {
        aleatorio = qrand()%saltos;
        vectorSalida->push_back(QPointF(i+aleatorio,datosAnalisis[i+aleatorio]));
    }

    return vectorSalida;
}

short* WQ_Validator::analisisSeriesTiempo(int numDatos)
{
    return vectorDatos->at(numDatos);
}

short* WQ_Validator::analisisFuncionProbabilidad(int numDatos)
{
    int numMaxPkgPorMicro = 60000000;
    short* datosSalida = new short[numMaxPkgPorMicro];
    for (int i = 0; i < numMaxPkgPorMicro; ++i) datosSalida[i]=0;

    for (int i = 0; i < 60000000; ++i) {
        datosSalida[vectorDatos->at(numDatos)[i]]++;
    }

    return datosSalida;
}

short* WQ_Validator::analisisAutocorrelacionM(int numDatos, int m)
{
    return vectorDatos->at(numDatos);
}

short* WQ_Validator::analisisHvsM(int numDatos)
{
    return vectorDatos->at(numDatos);
}
