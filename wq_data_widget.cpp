#include "wq_data_widget.h"
#include "ui_wq_data_widget.h"

WQ_Data_Widget::WQ_Data_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WQ_Data_Widget)
{
    ui->setupUi(this);
    vectorNombres = new QVector<QLabel*>();
    vectorBotonesRemove = new QVector<WQ_Button*>();
    ui->widgetTotalFiles->setMinimumSize(293,292);
    ui->widgetTotalFiles->setMaximumSize(293,292);
}

WQ_Data_Widget::~WQ_Data_Widget()
{
    delete ui;
}

void WQ_Data_Widget::agregarArchivo(QString nombreArchivo)
{
    //Creo los objetos
    int numArchivos = vectorNombres->size();
    QLabel* etiqueta = new QLabel(nombreArchivo,ui->widgetTotalFiles);
    WQ_Button* botonRemove = new WQ_Button(QIcon("Imagenes/Remove1.png"),"",ui->widgetTotalFiles, numArchivos);
    botonRemove->setIconSize(QSize(19,19));

    //Hago los conect necesarios
    connect(botonRemove,SIGNAL(pulsado(int)),this,SLOT(eliminarArchivoDataWidget(int)));

    //los agrego a la interfaz
    etiqueta->setGeometry(10, numArchivos*31+3, 240, 25);
    botonRemove->setGeometry(260, numArchivos*31+3, 25, 25);
    etiqueta->setVisible(true);
    botonRemove->setVisible(true);

    //Agrego los objetos a los vectores
    vectorNombres->push_back(etiqueta);
    vectorBotonesRemove->push_back(botonRemove);

    //Actualizo el tamaño del widget
    ui->widgetTotalFiles->setMinimumSize(293,(numArchivos+1)*31+3);
    ui->widgetTotalFiles->setMaximumSize(293,(numArchivos+1)*31+3);
}

void WQ_Data_Widget::eliminarArchivoDataWidget(int numFile)
{
    delete vectorNombres->at(numFile);
    vectorNombres->remove(numFile);

    delete vectorBotonesRemove->at(numFile);
    vectorBotonesRemove->remove(numFile);

    //Actualizar posición de los demás widgets
    int totalArchivos = vectorNombres->size();
    for (int i = numFile; i < totalArchivos; ++i)
    {
        vectorNombres->at(i)->setGeometry(10, i*31+3, 240, 25);
        vectorBotonesRemove->at(i)->setGeometry(260, i*31+3, 25, 25);
        vectorBotonesRemove->at(i)->setNumeroItem(i);
    }

    ui->widgetTotalFiles->setMinimumSize(293,totalArchivos*31+3);
    ui->widgetTotalFiles->setMaximumSize(293,totalArchivos*31+3);

    emit eliminarFileDataWidget(numFile);
}
