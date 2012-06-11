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
    ui->widgetCurvas->setGeometry(0,0,290,152);

    connect(ui->botonDeleteChart,SIGNAL(clicked()),this,SLOT(clickBotonEliminarChart()));
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
    WQ_Chart_Widget_Button* botonView = new WQ_Chart_Widget_Button(QIcon("Imagenes/View1.png"),"",ui->widgetCurvas, numCurvas);
    WQ_Chart_Widget_Button* botonRemove = new WQ_Chart_Widget_Button(QIcon("Imagenes/Remove1.png"),"",ui->widgetCurvas, numCurvas);

    //Hago los connects necesarios
    connect(botonRemove,SIGNAL(pulsado(int)),this,SLOT(eliminarCurva(int)));
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

    ui->widgetCurvas->setGeometry(0,0,290,(numCurvas+1)*31+3);
    return numCurvas;
}

void WQ_Chart_Widget::eliminarCurva(int numCurva)
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

    ui->widgetCurvas->setGeometry(0,0,290,(vectorNombres->size())*31+3);
    emit eliminarCurvaChart(numCurva);
}

void WQ_Chart_Widget::mostrarOcultarCurva(int numCurva)
{
    bool estado = vectorEstadoView->at(numCurva);
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
    ui->widgetTotal->setGeometry(0,0,anchoBase,largoBase+delta);
    ui->scrollArea->setGeometry(0,0,anchoBase,largoBase-37+delta);
    ui->widgetCurvas->setGeometry(0,0,anchoBase-15,largoBase-39+delta);
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
