#include "wq_validator.h"

WQ_Validator::WQ_Validator()
{
}

QVector<QPointF>** WQ_Validator::comparacionEscalasDeTiempo()
{
    ////////////////////// Codigo Basura /////////////////////////////
    QVector<QPointF>** salida = new QVector<QPointF>*[6];

    QVector<QPointF>* samples1 = new QVector<QPointF>;
    QVector<QPointF>* samples2 = new QVector<QPointF>;
    QVector<QPointF>* samples3 = new QVector<QPointF>;
    QVector<QPointF>* samples4 = new QVector<QPointF>;
    QVector<QPointF>* samples5 = new QVector<QPointF>;
    QVector<QPointF>* samples6 = new QVector<QPointF>;

    for (int i = 0; i < 1000; ++i)
        samples1->push_back(QPointF( ((double)(i))/10.0, sin(((double)(i))/3.0) ));

    for (int i = 0; i < 2000; ++i)
        samples2->push_back(QPointF( ((double)(i))/10.0, sin(((double)(i))/5.0) ));

    for (int i = 0; i < 3000; ++i)
        samples3->push_back(QPointF( ((double)(i))/10.0, sin(((double)(i))/7.0) ));

    for (int i = 0; i < 4000; ++i)
        samples4->push_back(QPointF( ((double)(i))/10.0, sin(((double)(i))/11.0) ));

    for (int i = 0; i < 5000; ++i)
        samples5->push_back(QPointF( ((double)(i))/10.0, sin(((double)(i))/13.0) ));

    for (int i = 0; i < 6000; ++i)
        samples6->push_back(QPointF( ((double)(i))/10.0, sin(((double)(i))/17.0) ));

    salida[0]=samples1;
    salida[1]=samples2;
    salida[2]=samples3;
    salida[3]=samples4;
    salida[4]=samples5;
    salida[5]=samples6;

    return salida;
    //////////////////////////////////////////////////////////////////
}
