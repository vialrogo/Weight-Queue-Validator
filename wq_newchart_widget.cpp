#include "wq_newchart_widget.h"
#include "ui_wq_newchart_widget.h"

WQ_NewChart_Widget::WQ_NewChart_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WQ_NewChart_Widget)
{
    ui->setupUi(this);

    //Objetos analisis

    //Objetos simulacion
}

WQ_NewChart_Widget::~WQ_NewChart_Widget()
{
    delete ui;
}

void WQ_NewChart_Widget::configurarWidgetAnalisis()
{

}

void WQ_NewChart_Widget::configurarWidgetSimulacion()
{

}
