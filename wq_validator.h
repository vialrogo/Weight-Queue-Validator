#ifndef WQ_VALIDATOR_H
#define WQ_VALIDATOR_H

#include <QVector>
#include <QPointF>
#include <math.h>

class WQ_Validator
{
private:
    QVector<short*> vectorDatos;

public:
    WQ_Validator();
    ~WQ_Validator();
    void agregarDatos(short* datos);
    void eliminarDatos(int numDato);
    QVector<QPointF>* obtenerVectorDatos(int numDatos, int inicio, int fin);
};

#endif // WQ_VALIDATOR_H
