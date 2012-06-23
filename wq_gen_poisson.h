#ifndef WQ_GEN_POISSON_H
#define WQ_GEN_POISSON_H

#include "wq_generator.h"

class WQ_Gen_Poisson: public WQ_Generator
{
    Q_OBJECT

private:
    short* datosGenerados;
    int parametro;

protected:
    void run();

public:
    WQ_Gen_Poisson(QObject *parent = 0);
    ~WQ_Gen_Poisson();
    void generarDatosSinteticos(double parametro_in=1.8);
};

#endif // WQ_GEN_POISSON_H
