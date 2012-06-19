#ifndef WQ_VALIDATOR_H
#define WQ_VALIDATOR_H

#define LIMITE_GRAFICA 1000000

#include <QVector>
#include <QPointF>

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
