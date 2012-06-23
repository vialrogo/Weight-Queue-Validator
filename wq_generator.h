#ifndef WQ_GENERATOR_H
#define WQ_GENERATOR_H

#include <QThread>
#include <time.h>
#include <cmath>

class WQ_Generator: public QThread
{
    Q_OBJECT

private:
    double semilla;
    double a;
    double m;

protected:
    void run();

public:
    WQ_Generator(QObject *parent = 0);
    virtual ~WQ_Generator();
    double generarNumeroAleatorio();

signals:
    void datosGeneradosExitosamente(QString nombreDatos, short* datos);
};

#endif // WQ_GENERATOR_H
