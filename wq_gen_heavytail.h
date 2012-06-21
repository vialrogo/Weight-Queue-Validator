#ifndef WQ_GEN_HEAVYTAIL_H
#define WQ_GEN_HEAVYTAIL_H

#include "wq_generator.h"

class WQ_Gen_HeavyTail: public WQ_Generator
{
    Q_OBJECT

public:
    WQ_Gen_HeavyTail(QObject *parent = 0);
    ~WQ_Gen_HeavyTail();
    short* generarDatosSinteticos(double parametro);
};

#endif // WQ_GEN_HEAVYTAIL_H
