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
    //Creo el arreglo con el conteo en milisegundos
    int* arregloEnMilis = new int[60000];
    for (int i = 0; i < 60000; ++i) arregloEnMilis[i]=0;
    for (int i = 0; i < 60000000; ++i) arregloEnMilis[i/1000]+=vectorDatos->at(numDatos)[i];

    //Creo el arreglo con el conteo de las ocurrencias
    int numMaxPkgPorMili = 32000;
    double* datosSalida = new double[numMaxPkgPorMili];
    for (int i = 0; i < numMaxPkgPorMili; ++i) datosSalida[i]=0.0;
    for (int i = 0; i < 60000; ++i) datosSalida[arregloEnMilis[i]]++;

    //Proceso para quitar ceros
    int ultimoNocero=numMaxPkgPorMili-1;
    for (int i = numMaxPkgPorMili-1; i >= 0; i--){
        if(datosSalida[i]!=0)
        {
            ultimoNocero = i-1;
            break;
        }
    }

    //Creo el arreglo de salida
    QVector<QPointF>* vectorSalida = new QVector<QPointF>();
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
