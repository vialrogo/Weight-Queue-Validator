#ifndef WQ_GENERATOR_H
#define WQ_GENERATOR_H

#include <QTime>
#include <cmath>

class WQ_Generator: public QObject
{
    Q_OBJECT

public:
    WQ_Generator(QObject *parent = 0);
    virtual ~WQ_Generator();
    double generarNumeroAleatorio();
};

#endif // WQ_GENERATOR_H
