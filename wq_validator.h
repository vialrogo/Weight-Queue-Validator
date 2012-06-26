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

public:
    WQ_Validator();
    ~WQ_Validator();
    void agregarDatos(short* datos);
    void eliminarDatos(int numDato);
    QVector<QPointF>* obtenerVectorDatos(int numDatos, int tipoAnalisis, int inicio, int fin);
    short* analisisSeriesTiempo(int numDatos);
    short* analisisFuncionProbabilidad(int numDatos);
    short* analisisAutocorrelacionM(int numDatos, int m);
    short* analisisHvsM(int numDatos);
};

#endif // WQ_VALIDATOR_H
