#include "wq_chart_widget.h"
#include "ui_wq_chart_widget.h"

WQ_Chart_Widget::WQ_Chart_Widget(QWidget *parent, int numChart_in) :
    QWidget(parent),
    ui(new Ui::WQ_Chart_Widget)
{
    ui->setupUi(this);
    numeroChart=numChart_in;
    vectorNombres = new QVector<QLabel*>();
    vectorBotonesView = new QVector<WQ_Chart_Widget_Button*>();
    vectorBotonesRemove = new QVector<WQ_Chart_Widget_Button*>();
    vectorEstadoView = new QVector<bool>();
    ui->widgetCurvas->setMinimumSize(290,152);
    ui->widgetCurvas->setMaximumSize(290,152);

    //Creo las fuentes para los labels
    fontNormal = new QFont();
    fontHide = new QFont();
    fontHide->setStrikeOut(true);

    connect(ui->botonDeleteChart,SIGNAL(clicked()),this,SLOT(clickBotonEliminarChart()));
    connect(ui->checkBoxXScroll,SIGNAL(stateChanged(int)),this,SLOT(pulsoCheckboxX(int)));
    connect(ui->checkBoxYScroll,SIGNAL(stateChanged(int)),this,SLOT(pulsoCheckboxY(int)));
}

WQ_Chart_Widget::~WQ_Chart_Widget()
{
    delete ui;
}

int WQ_Chart_Widget::agregarCurva(QString nombreCurva)
{
    //Creo los objetos
    int numCurvas = vectorNombres->size();
    QLabel* etiqueta = new QLabel(nombreCurva,ui->widgetCurvas);
    etiqueta->setFont(*fontNormal);
    WQ_Chart_Widget_Button* botonView = new WQ_Chart_Widget_Button(QIcon("Imagenes/View1.png"),"",ui->widgetCurvas, numCurvas);
    WQ_Chart_Widget_Button* botonRemove = new WQ_Chart_Widget_Button(QIcon("Imagenes/Remove1.png"),"",ui->widgetCurvas, numCurvas);

    //Hago los connects necesarios
    connect(botonRemove,SIGNAL(pulsado(int)),this,SLOT(eliminarCurvaChartWidget(int)));
    connect(botonView,SIGNAL(pulsado(int)),this,SLOT(mostrarOcultarCurva(int)));

    //los agrego a la interfaz
    etiqueta->setGeometry(10, numCurvas*31+3, 205, 25);
    botonView->setGeometry(225, numCurvas*31+3, 25, 25);
    botonRemove->setGeometry(260, numCurvas*31+3, 25, 25);

    //agrego los objetos a los vectores
    vectorNombres->push_back(etiqueta);
    vectorBotonesView->push_back(botonView);
    vectorBotonesRemove->push_back(botonRemove);
    vectorEstadoView->push_back(true);

    ui->widgetCurvas->setMinimumSize(290,(numCurvas+1)*31+3);
    ui->widgetCurvas->setMaximumSize(290,(numCurvas+1)*31+3);
    return numCurvas;
}

void WQ_Chart_Widget::eliminarCurvaChartWidget(int numCurva)
{
    delete vectorNombres->at(numCurva);
    vectorNombres->remove(numCurva);

    delete vectorBotonesView->at(numCurva);
    vectorBotonesView->remove(numCurva);

    delete vectorBotonesRemove->at(numCurva);
    vectorBotonesRemove->remove(numCurva);

    vectorEstadoView->remove(numCurva);

    //Actualizar posición de los demás widgets
    int totalCurvas = vectorNombres->size();
    for (int i = numCurva; i < totalCurvas; ++i)
    {
        vectorNombres->at(i)->setGeometry(10, i*31+3, 205, 25);
        vectorBotonesView->at(i)->setGeometry(225, i*31+3, 25, 25);
        vectorBotonesRemove->at(i)->setGeometry(260, i*31+3, 25, 25);

        vectorBotonesView->at(i)->setNumeroCurva(i);
        vectorBotonesRemove->at(i)->setNumeroCurva(i);
    }

    ui->widgetCurvas->setMinimumSize(290,(vectorNombres->size())*31+3);
    ui->widgetCurvas->setMaximumSize(290,(vectorNombres->size())*31+3);
    emit eliminarCurvaChart(numCurva);
}

void WQ_Chart_Widget::mostrarOcultarCurva(int numCurva)
{
    bool estado = vectorEstadoView->at(numCurva);
    vectorNombres->at(numCurva)->setFont(estado? *fontHide : *fontNormal);
    vectorEstadoView->remove(numCurva);
    vectorEstadoView->insert(numCurva, !estado);
    vectorBotonesView->at(numCurva)->setIcon(QIcon(estado? "Imagenes/View2.png" : "Imagenes/View1.png"));
    emit mostrarOcultarCurvaChart(numCurva, !estado);
}

void WQ_Chart_Widget::cambiarGeometriaNumeroCharts(int numCharts)
{
    int delta = (6-numCharts)*35;
    int anchoBase =305;
    int largoBase = 139;

    setMinimumSize(anchoBase,largoBase+delta);
    setMaximumSize(anchoBase,largoBase+delta);

    ui->widgetTotal->setMinimumSize(anchoBase,largoBase+delta);
    ui->widgetTotal->setMaximumSize(anchoBase,largoBase+delta);

    ui->scrollArea->setMinimumSize(anchoBase,largoBase-37+delta);
    ui->scrollArea->setMaximumSize(anchoBase,largoBase-37+delta);

    ui->checkBoxXScroll->setGeometry(5,largoBase-32+delta,75,30);
    ui->checkBoxYScroll->setGeometry(85,largoBase-32+delta,75,30);
    ui->botonDeleteChart->setGeometry(210,largoBase-32+delta,94,30);
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

void WQ_Chart_Widget::pulsoCheckboxX(int iestado)
{
    emit cambiarScrollX(iestado!=0);
}

void WQ_Chart_Widget::pulsoCheckboxY(int iestado)
{
    emit cambiarScrollY(iestado!=0);
}
