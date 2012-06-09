#include "wq_validator.h"

WQ_Validator::WQ_Validator()
{
}

QVector<QPointF>** WQ_Validator::comparacionEscalasDeTiempo()
{
    QVector<QPointF>** salida = new QVector<QPointF>*[3];

    ////////////////////// Codigo Basura /////////////////////////////
    QVector<QPointF>* samples1 = new QVector<QPointF>;
    QVector<QPointF>* samples2 = new QVector<QPointF>;
    QVector<QPointF>* samples3 = new QVector<QPointF>;

    for (int i = 0; i < 2000; ++i)
        samples1->push_back(QPointF( ((double)(i))/10.0, sin(((double)(i))/10.0) ));

    for (int i = 0; i < 1000; ++i)
        samples2->push_back(QPointF( ((double)(i))/10.0, sin(((double)(i))/10.0) ));

    for (int i = 0; i < 3000; ++i)
        samples3->push_back(QPointF( ((double)(i))/10.0, sin(((double)(i))/10.0) ));

    salida[0]=samples1;
    salida[1]=samples2;
    salida[2]=samples3;
    //////////////////////////////////////////////////////////////////

    return salida;
}
