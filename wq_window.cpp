#include "wq_window.h"

WQ_Window::WQ_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WQ_Window)
{
    ui->setupUi(this);

    //Defino los gráficos que se van a dibujar
    grafico1 = new WQ_Chart(ui->widgetChart1, QSize(330,200));
    grafico2 = new WQ_Chart(ui->widgetChart2, QSize(330,200));
    grafico3 = new WQ_Chart(ui->widgetChart3, QSize(330,200));

    //Inicialización de otras variables
    radioButtonSeleccionado=0;

    connect(ui->radioButtonAnalisis1,SIGNAL(clicked()),this,SLOT(comparacionEscalasDeTiempo()));
    connect(ui->radioButtonAnalisis2,SIGNAL(clicked()),this,SLOT(comparacionFuncionesProbabilidad()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(acercaDe()));
    connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(close()));
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

        //Creo las curvas que voy a pintar
        grafico1->adicionarCurva("curva");
        grafico2->adicionarCurva("curva");
        grafico3->adicionarCurva("curva");

        //Agrego las etiquetas a los ejes
        grafico1->agregarEtiquetas("tiempo","datos");
        grafico2->agregarEtiquetas("tiempo","datos");
        grafico3->agregarEtiquetas("tiempo","datos");

        ////////////////////// Codigo Basura /////////////////////////////
        QVector<QPointF>* samples = new QVector<QPointF>;

        double id;
        for (int i = 0; i < 200; ++i)
        {
            id=(double)(i);
            samples->push_back(QPointF( id/10.0 , sin(id/10.0) ));
        }

        grafico1->agregarDatosACurva("curva",samples);
        grafico2->agregarDatosACurva("curva",samples);
        grafico3->agregarDatosACurva("curva",samples);

        //////////////////////////////////////////////////////////////////
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
