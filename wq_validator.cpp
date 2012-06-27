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
    if(tipoAnalisis==0) return analisisSeriesTiempo(numDatos, inicio, fin);
    if(tipoAnalisis==1) return analisisFuncionProbabilidad(numDatos);
    if(tipoAnalisis==2) return analisisAutocorrelacionM(numDatos, 1 /* Ojo!! */);
    if(tipoAnalisis==3) return analisisHvsM(numDatos);
}

QVector<QPointF>* WQ_Validator::analisisSeriesTiempo(int numDatos, int inicio, int fin)
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
        vectorSalida->push_back(QPointF(i+aleatorio,vectorDatos->at(numDatos)[i+aleatorio]));
    }

    return vectorSalida;
}

QVector<QPointF>* WQ_Validator::analisisFuncionProbabilidad(int numDatos)
{
    QVector<QPointF>* vectorSalida = new QVector<QPointF>();
    int numMaxPkgPorMicro = 60000; //Valor puesto a ojo, puede aumentar
    double* datosSalida = new double[numMaxPkgPorMicro];

    for (int i = 0; i < numMaxPkgPorMicro; ++i) datosSalida[i]=0.0;

    for (int i = 0; i < 60000000; ++i) datosSalida[vectorDatos->at(numDatos)[i]]++;

    //Proceso para quitar ceros
    int ultimoNocero=numMaxPkgPorMicro-1;
    for (int i = numMaxPkgPorMicro-1; i >= 0; i--){
        if(datosSalida[i]!=0)
        {
            ultimoNocero = i-1;
            break;
        }
    } // fin del proceso para quitar ceros

    for (int i = 0; i < ultimoNocero*2; ++i) vectorSalida->push_back(QPointF(i,datosSalida[i]));

    return vectorSalida;
}

QVector<QPointF>* WQ_Validator::analisisAutocorrelacionM(int numDatos, int m)
{
    QVector<QPointF>* vectorSalida = new QVector<QPointF>();
    return vectorSalida;
}

QVector<QPointF>* WQ_Validator::analisisHvsM(int numDatos)
{
    QVector<QPointF>* vectorSalida = new QVector<QPointF>();
    return vectorSalida;
}
