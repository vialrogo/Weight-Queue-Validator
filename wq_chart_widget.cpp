#include "wq_chart_widget.h"
#include "ui_wq_chart_widget.h"

WQ_Chart_Widget::WQ_Chart_Widget(QWidget *parent, int numChart_in) :
    QWidget(parent),
    ui(new Ui::WQ_Chart_Widget)
{
    ui->setupUi(this);
    numeroChart=numChart_in;
    vectorNombres = new QVector<QLabel*>();
    vectorBotonesView = new QVector<QPushButton*>();
    vectorBotonesRemove = new QVector<QPushButton*>();
    ui->widgetCurvas->setMinimumSize(290,5);

    connect(ui->botonDeleteChart,SIGNAL(clicked()),this,SLOT(clickBotonEliminarChart()));
}

WQ_Chart_Widget::~WQ_Chart_Widget()
{
    delete ui;
}

int WQ_Chart_Widget::agregarCurva(QString nombreCurva)
{
    int numCurvas = vectorNombres->size();
    QLabel* etiqueta = new QLabel(nombreCurva,ui->widgetCurvas);
    QPushButton* botonView = new QPushButton(QIcon("Imagenes/View1.png"),"",ui->widgetCurvas);
    QPushButton* botonRemove = new QPushButton(QIcon("Imagenes/Remove1.png"),"",ui->widgetCurvas);

    etiqueta->setGeometry(0, numCurvas*30, 210, 25);
    botonView->setGeometry(220, numCurvas*30, 25, 25);
    botonRemove->setGeometry(255, numCurvas*30, 25, 25);

    vectorNombres->push_back(etiqueta);
    vectorBotonesView->push_back(botonView);
    vectorBotonesRemove->push_back(botonRemove);

    ui->widgetCurvas->setMinimumSize(290,(numCurvas+1)*30);

    return numCurvas;
}

void WQ_Chart_Widget::clickBotonEliminarChart()
{
    emit eliminarChart(numeroChart);
}

int WQ_Chart_Widget::getNumChart()
{
    return numeroChart;
}

void WQ_Chart_Widget::setNumChart(int numeroChart_in)
{
    numeroChart=numeroChart_in;
}
