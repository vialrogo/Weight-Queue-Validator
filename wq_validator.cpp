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

QVector<QPointF>* WQ_Validator::obtenerVectorDatos(int numDatos, int tipoAnalisis, int inicio, int fin, int hlimit)
{
    if(tipoAnalisis==0) return analisisSeriesTiempo(numDatos, inicio, fin);
    else if(tipoAnalisis==1) return analisisFuncionProbabilidad(numDatos);
    else if(tipoAnalisis==2) return analisisAutocorrelacionM(numDatos, 1);
    else return analisisHvsM(numDatos,hlimit);
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
    for (int i = 0; i < ultimoNocero+1; ++i) vectorSalida->push_back(QPointF(i+errorIndeterLog,datosSalida[i]+errorIndeterLog));

    return vectorSalida;
}

QVector<QPointF>* WQ_Validator::analisisAutocorrelacionM(int numDatos, int m)
{
    /// Parámetros quemados en código ///
    int numDecimar=1;
    int numAuto=1000;
    /// /////////////////////////////////

    int cantidadDatos = 60000000/(m*numDecimar);
    double* arregloDatosPorM = new double[cantidadDatos];
    for (int i = 0; i < cantidadDatos; ++i) arregloDatosPorM[i]=0;
    calcularVectorM(arregloDatosPorM,m,numDecimar,numDatos);

    //Calculo de media
    double media = 0.0;
    for (int t = 0; t < cantidadDatos; ++t) media+=arregloDatosPorM[t];
    media = media/((double)cantidadDatos);

    //Calculo de la varianza sin dividir
    double varianzaG = 0.0;
    for (int t = 0; t < cantidadDatos; ++t) varianzaG+= pow(( (double)(arregloDatosPorM[t]) - media ), 2);

    //Calculo de la autocorrelación
    double numerador=0.0;
    double* autocorrelacion = new double[numAuto];
    for (int k = 0; k < numAuto; ++k) autocorrelacion[k]=0.0;
    for (int k = 1; k < numAuto; ++k)
    {
        numerador=0.0;
        for (int t = 0; t < cantidadDatos-k; ++t)
        {
            numerador+= (( (double)(arregloDatosPorM[t]) - media ) * ( (double)(arregloDatosPorM[t+k]) - media ) );
        }
        autocorrelacion[k]=numerador / varianzaG;
    }

    //Creo el arreglo de salida
    double errorIndeterLog=0.1;
    QVector<QPointF>* vectorSalida = new QVector<QPointF>();
    for (int k = 0; k < numAuto; ++k) vectorSalida->push_back(QPointF(k+errorIndeterLog,autocorrelacion[k]+errorIndeterLog));

    //Elimino los punteros creados
    delete arregloDatosPorM;
    delete autocorrelacion;

    //Salida
    return vectorSalida;
}

void WQ_Validator::calcularVectorM(double *arregloDatosPorM, int m, int numDecimar, int numData)
{   
    //Decimar y promediar
    for (int i = 0; i < 60000000/(m*numDecimar); i++)
    {
        for (int j = 0; j < m; ++j)
        {
            arregloDatosPorM[i]+=vectorDatos->at(numData)[(i+j)*numDecimar + (int)(qrand()%numDecimar)];
        }
        arregloDatosPorM[i]=arregloDatosPorM[i]/((double)m);
    }
}

QVector<QPointF>* WQ_Validator::analisisHvsM(int numDatos, int maximoM)
{
    QVector<QPointF>* vectorSalida = new QVector<QPointF>();
    QVector<QPointF>* vectorTemporal;
    double h;

    for (int i = 1; i <= maximoM; ++i)
    {
        vectorTemporal = analisisAutocorrelacionM(numDatos,i);
        h = calcularPendienteMinimosCuadrados(vectorTemporal);
        vectorSalida->push_back(QPointF(i,h));
        delete vectorTemporal;
    }

    return vectorSalida;
}

double WQ_Validator::calcularPendienteMinimosCuadrados(QVector<QPointF> *vectorDatosIn)
{
    int tamanho = vectorDatosIn->size();
    QPointF puntoTemporal;

    double X;
    double Y;
    double term1=0.0;
    double term2=0.0;
    double term3=0.0;
    double term4=0.0;

    for (int i = 0; i < tamanho; ++i)
    {
        puntoTemporal = vectorDatosIn->at(i);
        X = log10(puntoTemporal.rx());
        Y = log10(puntoTemporal.ry());

        term1+=X;
        term2+=Y;
        term3+=X*Y;
        term4+=X*X;
    }

    double pendiente = (tamanho*term3 - term1*term2) / (tamanho*term4 - term1*term1);
    return (1.0 - (pendiente/2.0));
}
