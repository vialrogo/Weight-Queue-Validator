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
    else if(tipoAnalisis==1) return analisisFuncionProbabilidad(numDatos);
    else if(tipoAnalisis==2) return analisisAutocorrelacionM(numDatos, 1 /* Ojo!! */);
    else return analisisHvsM(numDatos);
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
    //Creo el arreglo con el conteo de las ocurrencias
    int numMaxPkgPorMicro = 2000;
    double* datosSalida = new double[numMaxPkgPorMicro];
    for (int i = 0; i < numMaxPkgPorMicro; ++i) datosSalida[i]=0.0;
    for (int i = 0; i < 60000000; ++i) datosSalida[vectorDatos->at(numDatos)[i]]++;

    //Proceso para detectar ultimo cero
    int ultimoNocero=numMaxPkgPorMicro-1;
    for (int i = numMaxPkgPorMicro-1; i >= 0; i--){
        if(datosSalida[i]!=0)
        {
            ultimoNocero = i-1;
            break;
        }
    }

    //Creo el arreglo de salida
    double errorIndeterLog=0.1;
    QVector<QPointF>* vectorSalida = new QVector<QPointF>();
    for (int i = 0; i < ultimoNocero+4; ++i) vectorSalida->push_back(QPointF(i+errorIndeterLog,datosSalida[i]+errorIndeterLog));

    return vectorSalida;
}

QVector<QPointF>* WQ_Validator::analisisAutocorrelacionM(int numDatos, int m)
{
    /// por el momento voy a ignorar m, ya que luego lo hago m=1


    //Calculo de media
    double media = 0.0;
    for (int t = 0; t < 60000000; ++t) media+=vectorDatos->at(numDatos)[t];
    media = media/60000000.0;

    //Calculo de la varianza sin dividir
    double varianzaG = 0.0;
    for (int t = 0; t < 60000000; ++t) varianzaG+= pow(( (double)(vectorDatos->at(numDatos)[t]) - media ), 2);

    //Calculo de la autocorrelación
    double numerador=0.0;
    int numAuto=60;
    double* autocorrelacion = new double[numAuto];
    for (int k = 0; k < numAuto; ++k) autocorrelacion[k]=0.0;
    for (int k = 1; k < numAuto; ++k)
    {
        numerador=0.0;
        for (int t = 0; t < 60000000-k; ++t)
        {
            numerador+= (( (double)(vectorDatos->at(numDatos)[t]) - media ) * ( (double)(vectorDatos->at(numDatos)[t+k]) - media ) );
        }
        autocorrelacion[k]=numerador / varianzaG;
    }

    //Creo el arreglo de salida
    double errorIndeterLog=0.1;
    QVector<QPointF>* vectorSalida = new QVector<QPointF>();
    for (int k = 0; k < numAuto; ++k) vectorSalida->push_back(QPointF(k+errorIndeterLog,autocorrelacion[k]+errorIndeterLog));
    return vectorSalida;
}

QVector<QPointF>* WQ_Validator::analisisHvsM(int numDatos)
{
    QVector<QPointF>* vectorSalida = new QVector<QPointF>();
    return vectorSalida;
}
