#include "wq_window.h"

WQ_Window::WQ_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WQ_Window)
{
    ui->setupUi(this);
    tamanoEstandarGrafico= QSize(330,200);
    radioButtonSeleccionado=0;
    numeroWidgetsUsados=0;
    validador = new WQ_Validator();
    arregoWidgets = new QWidget*[6];

    for (int i = 0; i < 6; ++i)
    {
        arregoWidgets[i]=new QWidget(this);
        arregoWidgets[i]->setMaximumSize(330,200);
        arregoWidgets[i]->setMinimumSize(330,200);
        arregoWidgets[i]->setGeometry(324+((i%2)*360), 40+((i/2)*220), 330, 200);
        arregoWidgets[i]->setVisible(true);
        agregarQuitarBordeWidgets(i,true);
    }

    connect(ui->radioButtonAnalisis1,SIGNAL(clicked()),this,SLOT(comparacionEscalasDeTiempo()));
    connect(ui->radioButtonAnalisis2,SIGNAL(clicked()),this,SLOT(comparacionFuncionesProbabilidad()));
    connect(ui->radioButtonAnalisis3,SIGNAL(clicked()),this,SLOT(comparacion3NombreTemporal()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(acercaDe()));
    connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(close()));
}

WQ_Window::~WQ_Window()
{
    delete ui;
}

void WQ_Window::agregarQuitarBordeWidgets(int numWidget, bool bordeBool)
{
    arregoWidgets[numWidget]->setStyleSheet(bordeBool? "border: 2px dotted gray; border-radius: 3px;" : "");
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

int WQ_Window::agregarChart()
{
    if(numeroWidgetsUsados<6)
    {
        agregarQuitarBordeWidgets(numeroWidgetsUsados,false);
        WQ_Chart* nuevoChart = new WQ_Chart(arregoWidgets[numeroWidgetsUsados], tamanoEstandarGrafico);
        vectorCharts.append(nuevoChart);
        nuevoChart->setVisible(true);
        numeroWidgetsUsados++;
        return vectorCharts.size()-1;
    }
    else
    {
        qDebug("intento agregar un widget de mas");
        return -1;
    }
}

void WQ_Window::comparacionEscalasDeTiempo()
{
    if(radioButtonSeleccionado!=1) //Esto hay que hacerlo dinámico
    {
        radioButtonSeleccionado=1;
        QString nombreSeries="serieDeTiempo";
        QVector<QPointF>** vectoresGraficas = validador->comparacionEscalasDeTiempo();

        //Quito los punteados, defino los gráficos que se van a dibujar y hago que las gráficas se vean
        int chart1 = agregarChart();
        int chart2 = agregarChart();
        int chart3 = agregarChart();

        //Creo las curvas que voy a pintar y la serie que corresponde
        vectorCharts[chart1]->agregarCurva(nombreSeries,vectoresGraficas[0]);
        vectorCharts[chart2]->agregarCurva(nombreSeries,vectoresGraficas[1]);
        vectorCharts[chart3]->agregarCurva(nombreSeries,vectoresGraficas[2]);

        //Agrego las etiquetas a los ejes
//        vectorCharts[chart1]->agregarEtiquetas("Tiempo","Datos");
//        vectorCharts[chart2]->agregarEtiquetas("Tiempo","Datos");
//        vectorCharts[chart3]->agregarEtiquetas("Tiempo","Datos");

        //Temporal
        vectorCharts[chart1]->setAxisScale(WQ_Chart::xBottom, 0.0, 10.0);
    }
}

void WQ_Window::comparacionFuncionesProbabilidad()
{
    if(radioButtonSeleccionado!=2)
    {
        radioButtonSeleccionado=2;
        qDebug("Escogio comparacion por funciones probabilisticas");

        delete vectorCharts[0];
        vectorCharts.pop_front();
        numeroWidgetsUsados--;
        delete vectorCharts[0];
        vectorCharts.pop_front();
        numeroWidgetsUsados--;
        delete vectorCharts[0];
        vectorCharts.pop_front();
        numeroWidgetsUsados--;

        agregarQuitarBordeWidgets(0, true);
        agregarQuitarBordeWidgets(1, true);
        agregarQuitarBordeWidgets(2, true);
    }
}

void WQ_Window::comparacion3NombreTemporal()
{
    if(radioButtonSeleccionado!=3)
    {
        radioButtonSeleccionado=3;
    }
}
