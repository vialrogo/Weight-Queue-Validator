#include "wq_analysing_widget.h"
#include "ui_wq_newchart_widget.h"

WQ_Analysing_Widget::WQ_Analysing_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WQ_Analysing_Widget)
{
    ui->setupUi(this);

    //Objetos analisis

    //Objetos simulacion

    connect(ui->radioButtonAnalisis,SIGNAL(clicked()),this,SLOT(escogioAnalisis()));
    connect(ui->radioButtonSimulacion,SIGNAL(clicked()),this,SLOT(escogioSimulacion()));
}

WQ_Analysing_Widget::~WQ_Analysing_Widget()
{
    delete ui;
}

void WQ_Analysing_Widget::configurarWidgetAnalisis()
{

}

void WQ_Analysing_Widget::configurarWidgetSimulacion()
{

}

void WQ_Analysing_Widget::escogioAnalisis()
{
    emit analizar();
}

void WQ_Analysing_Widget::escogioSimulacion()
{
    emit simular();
}
