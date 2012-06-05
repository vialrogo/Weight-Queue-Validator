//Includes del proyecto
#include "wq_window.h"
#include "ui_wq_window.h"
#include "wq_chart.h"

//Includes de QWT
#include <qwt_plot_curve.h>
#include <qwt_series_data.h>
#include <qwt_scale_draw.h>
#include <qwt_plot_rescaler.h>

//Includes de QT
#include <QMessageBox>

//Includes Temporales
#include <math.h>

WQ_Window::WQ_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WQ_Window)
{
    ui->setupUi(this);

    //Defino los gráficos que se van a dibujar
    WQ_Chart* grafico1 = new WQ_Chart(ui->widgetChart1);
    WQ_Chart* grafico2 = new WQ_Chart(ui->widgetChart2);
    WQ_Chart* grafico3 = new WQ_Chart(ui->widgetChart3);
    grafico1->setAutoReplot(true);
    grafico2->setAutoReplot(true);
    grafico3->setAutoReplot(true);

    //Ajusto el tamanho
    grafico1->setMinimumSize(300,180);
    grafico2->setMinimumSize(300,180);
    grafico3->setMinimumSize(300,180);

    grafico1->setMaximumSize(300,180);
    grafico2->setMaximumSize(300,180);
    grafico3->setMaximumSize(300,180);

    //Creo las curvas que voy a pintar
    QwtPlotCurve *curva1 = new QwtPlotCurve();
    QwtPlotCurve *curva2 = new QwtPlotCurve();
    QwtPlotCurve *curva3 = new QwtPlotCurve();
    curva1->attach(grafico1);
    curva2->attach(grafico2);
    curva3->attach(grafico3);

    //Inicialización de otras variables
    radioButtonSeleccionado=0;

    connect(ui->radioButtonAnalisis1,SIGNAL(clicked()),this,SLOT(comparacionEscalasDeTiempo()));
    connect(ui->radioButtonAnalisis2,SIGNAL(clicked()),this,SLOT(comparacionFuncionesProbabilidad()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(acercaDe()));
    connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(close()));

//    Temporatilo
//    grafico1->setAxisTitle( QwtPlot::xBottom, "time" );
//    grafico1->setAxisTitle( QwtPlot::yLeft, "data" );

    ////////////////////// Codigo Basura /////////////////////////////
    QwtPointSeriesData* myData = new QwtPointSeriesData;

    QVector<QPointF>* samples = new QVector<QPointF>;

    double id;
    for (int i = 0; i < 200; ++i)
    {
        id=(double)(i);
        samples->push_back(QPointF( id/10.0 , sin(id/10.0) ));
    }

    myData->setSamples(*samples);

    curva1->setData(myData);
    curva2->setData(myData);
    curva3->setData(myData);

    //////////////////////////////////////////////////////////////////

}

WQ_Window::~WQ_Window()
{
    delete ui;
}
void WQ_Window::acercaDe()
{
    QMessageBox msgBox;
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setWindowTitle("About");
    msgBox.setText("<h3>Weight Queue Validator</h3>");
    msgBox.setInformativeText("Create by: \n Victor Alberto Romero");
    msgBox.setIconPixmap(QPixmap("Imagenes/Fractal-Symmetric-Transparent_128x128.png"));
    msgBox.exec();
    return;
}

void WQ_Window::comparacionEscalasDeTiempo()
{
    if(radioButtonSeleccionado!=1)
    {
        radioButtonSeleccionado=1;
        qDebug("Escogio comparacion por escalas de tiempo");
    }
}

void WQ_Window::comparacionFuncionesProbabilidad()
{
    if(radioButtonSeleccionado!=2)
    {
        radioButtonSeleccionado=2;
        qDebug("Escogio comparacion por funciones probabilisticas");
    }
}
