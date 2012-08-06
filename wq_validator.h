#ifndef WQ_VALIDATOR_H
#define WQ_VALIDATOR_H

#include <QVector>
#include <QPointF>
#include <QTime>
#include <math.h>

class WQ_Validator
{
private:
    QVector<short*>* vectorDatos;
    double calcularPendienteMinimosCuadrados(QVector<QPointF>* vectorDatosIn);

public:
    WQ_Validator();
    ~WQ_Validator();
    void agregarDatos(short* datos);
    void eliminarDatos(int numDato);
    QVector<QPointF>* obtenerVectorDatos(int numDatos, int tipoAnalisis, int inicio, int fin, int hlimit);
    QVector<QPointF>* analisisSeriesTiempo(int numDatos, int inicio, int fin);
    QVector<QPointF>* analisisFuncionProbabilidad(int numDatos);
    QVector<QPointF>* analisisAutocorrelacionM(int numDatos, int m);
    QVector<QPointF>* analisisHvsM(int numDatos, int maximoM);
    void calcularVectorM(double* arregloDatosPorM, int m, int numDecimar, int numData);
};

#endif // WQ_VALIDATOR_H
