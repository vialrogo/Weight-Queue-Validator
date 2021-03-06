#ifndef WQ_GEN_HEAVYTAIL_H
#define WQ_GEN_HEAVYTAIL_H

#include "wq_generator.h"
#include <QVector>

class WQ_Gen_HeavyTail: public WQ_Generator
{
    Q_OBJECT

private:
    double parametro;
    double alfa;
    int truncamientoFuncion;

protected:
    void run();

public:
    WQ_Gen_HeavyTail(QObject *parent = 0);
    ~WQ_Gen_HeavyTail();
    void generarDatosSinteticos(double parametro_in, double alfa_in, int truncamiento_in);
};

#endif // WQ_GEN_HEAVYTAIL_H
