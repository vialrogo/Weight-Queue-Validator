#ifndef WQ_GENERATOR_H
#define WQ_GENERATOR_H

#include <QObject>
#include <time.h>
#include <cmath>

class WQ_Generator: public QObject
{
    Q_OBJECT

private:
    double semilla;
    double a;
    double m;

public:
    WQ_Generator(QObject *parent = 0);
    virtual ~WQ_Generator();
    double generarNumeroAleatorio();
};

#endif // WQ_GENERATOR_H
