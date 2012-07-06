#ifndef WQ_GEN_HEAVYTAIL_H
#define WQ_GEN_HEAVYTAIL_H

#include "wq_generator.h"
#include <QVector>

//temporal
#include <iostream>
using namespace std;

class WQ_Gen_HeavyTail: public WQ_Generator
{
    Q_OBJECT

private:
    double parametro;

protected:
    void run();

public:
    WQ_Gen_HeavyTail(QObject *parent = 0);
    ~WQ_Gen_HeavyTail();
    void generarDatosSinteticos(double parametro_in);
};

#endif // WQ_GEN_HEAVYTAIL_H
