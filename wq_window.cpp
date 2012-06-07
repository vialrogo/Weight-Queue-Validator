#include "wq_window.h"

WQ_Window::WQ_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WQ_Window)
{
    ui->setupUi(this);
    tamanoEstandarGrafico= QSize(330,200);
    radioButtonSeleccionado=0;
    validador = new WQ_Validator();

    for (int i = 0; i < 6; ++i) agregarQuitarBordeChart(i,true);

    connect(ui->radioButtonAnalisis1,SIGNAL(clicked()),this,SLOT(comparacionEscalasDeTiempo()));
    connect(ui->radioButtonAnalisis2,SIGNAL(clicked()),this,SLOT(comparacionFuncionesProbabilidad()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(acercaDe()));
    connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(close()));
}

WQ_Window::~WQ_Window()
{
    delete ui;
}

void WQ_Window::agregarQuitarBordeChart(int chart, bool bordeBool)
{
    QString borde="";

    if(bordeBool)
        borde = "border: 2px dotted gray; border-radius: 3px;";

    if(chart==0) ui->widgetChart0->setStyleSheet(borde);
    if(chart==1) ui->widgetChart1->setStyleSheet(borde);
    if(chart==2) ui->widgetChart2->setStyleSheet(borde);
    if(chart==3) ui->widgetChart3->setStyleSheet(borde);
    if(chart==4) ui->widgetChart4->setStyleSheet(borde);
    if(chart==5) ui->widgetChart5->setStyleSheet(borde);
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
    if(radioButtonSeleccionado!=1) //Esto hay que hacerlo dinámico
    {
        radioButtonSeleccionado=1;
        QString nombreSeries="serieDeTiempo";
        QVector<QPointF>** vectoresGraficas = validador->comparacionEscalasDeTiempo();

        //Quito los punteados
        agregarQuitarBordeChart(0, false);
        agregarQuitarBordeChart(1, false);
        agregarQuitarBordeChart(2, false);

        //Defino los gráficos que se van a dibujar
        grafico1 = new WQ_Chart(ui->widgetChart0, tamanoEstandarGrafico);
        grafico2 = new WQ_Chart(ui->widgetChart1, tamanoEstandarGrafico);
        grafico3 = new WQ_Chart(ui->widgetChart2, tamanoEstandarGrafico);

        //Hago que las gráficas se vean
        grafico1->setVisible(true);
        grafico2->setVisible(true);
        grafico3->setVisible(true);

        //Creo las curvas que voy a pintar
        grafico1->adicionarCurva(nombreSeries);
        grafico2->adicionarCurva(nombreSeries);
        grafico3->adicionarCurva(nombreSeries);

        //Agrego las etiquetas a los ejes
//        grafico1->agregarEtiquetas("Tiempo","Datos");
//        grafico2->agregarEtiquetas("Tiempo","Datos");
//        grafico3->agregarEtiquetas("Tiempo","Datos");

        //agrego a cada gráfico la serie que corresponde
        grafico1->agregarDatosACurva(nombreSeries,vectoresGraficas[0]);
        grafico2->agregarDatosACurva(nombreSeries,vectoresGraficas[1]);
        grafico3->agregarDatosACurva(nombreSeries,vectoresGraficas[2]);

        //Temporal
        grafico1->setAxisScale(WQ_Chart::xBottom, 0.0, 10.0);
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
