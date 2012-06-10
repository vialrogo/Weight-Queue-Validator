#include "wq_window.h"

WQ_Window::WQ_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WQ_Window)
{
    ui->setupUi(this);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    tamanoEstandarGrafico= QSize(330,200);
    radioButtonSeleccionado=0;
    numeroWidgetsUsados=0;
    validador = new WQ_Validator();
    arregoWidgets = new QWidget*[6];
    vectorCurvasPorChart = new QVector<QVector <QVector<QPointF>* >* >();

    for (int i = 0; i < 6; ++i)
    {
        arregoWidgets[i]=new QWidget(this);
        colocarWidgetEnPosicion(i,i);
        agregarQuitarBordeWidgets(i,true);
    }

    //Configuraciones de apariencia area
    QPalette p = ui->plainTextEditConsole->palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::white);
    ui->plainTextEditConsole->setPalette(p);

    //Agregar toolboox
    QToolBox* toolBoxCharts = new QToolBox(ui->tabExistente);
    toolBoxCharts->setGeometry(0,0,310,362);
    toolBoxCharts->setVisible(true);

//    QWidget* prueba1 = new QWidget();
//    QWidget* prueba2 = new QWidget();
//    QWidget* prueba3 = new QWidget();
//    QWidget* prueba4 = new QWidget();
//    QWidget* prueba5 = new QWidget();
//    QWidget* prueba6 = new QWidget();
//    toolBoxCharts->addItem(prueba1,"widget");
//    toolBoxCharts->addItem(prueba2,"widget");
//    toolBoxCharts->addItem(prueba3,"widget");
//    toolBoxCharts->addItem(prueba4,"widget");
//    toolBoxCharts->addItem(prueba5,"widget");
//    toolBoxCharts->addItem(prueba6,"widget");

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

void WQ_Window::colocarWidgetEnPosicion(int numWidget, int posicion)
{
    arregoWidgets[numWidget]->setMaximumSize(tamanoEstandarGrafico.width(),tamanoEstandarGrafico.height());
    arregoWidgets[numWidget]->setMinimumSize(tamanoEstandarGrafico.width(),tamanoEstandarGrafico.height());
    arregoWidgets[numWidget]->setGeometry(334+((posicion%2)*(tamanoEstandarGrafico.width()+20) ),
                                          40 +((posicion/2)*(tamanoEstandarGrafico.height()+20)),
                                          tamanoEstandarGrafico.width(),
                                          tamanoEstandarGrafico.height() );
}

int WQ_Window::agregarChart()
{
    if(numeroWidgetsUsados<6)
    {
        agregarQuitarBordeWidgets(numeroWidgetsUsados,false);

        //Creo y agrego el chart
        WQ_Chart* nuevoChart = new WQ_Chart(arregoWidgets[numeroWidgetsUsados], tamanoEstandarGrafico);
        vectorCharts.append(nuevoChart);

        //Creo y agrego su vector de curvas
        QVector<QVector<QPointF>* >* vectorCurvas = new QVector <QVector<QPointF>* > ();
        vectorCurvasPorChart->append(vectorCurvas);

        nuevoChart->setVisible(true);
        numeroWidgetsUsados++;
        salidaInformacion("Chart agregado exitosamente");
        return vectorCharts.size()-1;
    }
    else
    {
        salidaError("Intentó agregar un chart y no cabe");
        return -1;
    }
}

void WQ_Window::eliminarChart(int numChart)
{
    if(vectorCharts.size()>numChart)
    {
        QWidget* temporal;

        for (int i = numChart+1; i < vectorCharts.size(); ++i)
        {
            //Cambio la posición de los widgets en la interfaz
            colocarWidgetEnPosicion(i,i-1);
            colocarWidgetEnPosicion(i-1,i);

            //Troco los widgets en el arreglo
            temporal=arregoWidgets[i-1];
            arregoWidgets[i-1] = arregoWidgets[i];
            arregoWidgets[i]=temporal;
        }

        //Elimino el último chart
        delete vectorCharts[numChart];
        vectorCharts.remove(numChart);

        //Elimino todas las curvas del chart
        for (int i = 0; i < vectorCurvasPorChart->at(numChart)->size(); ++i) {
            delete vectorCurvasPorChart->at(numChart)->at(0);
            vectorCurvasPorChart->at(numChart)->remove(0);
        }
        delete vectorCurvasPorChart->at(numChart);
        vectorCurvasPorChart->remove(numChart);

        //Acomodo el último widget
        agregarQuitarBordeWidgets(numeroWidgetsUsados-1, true);
        numeroWidgetsUsados--;
    }
    else
    {
        salidaError("intentó quitar un chart que no existe");
    }
}

void WQ_Window::agregarCurvaAChart(int numChart, QString nombreCurva, QVector<QPointF> *datos)
{
    QVector<QVector<QPointF>* >* vectorCurvas = vectorCurvasPorChart->at(numChart);
    vectorCurvas->push_back(datos);
    vectorCharts[numChart]->agregarCurva(nombreCurva,datos);
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
        if(chart1!=-1) agregarCurvaAChart(chart1,nombreSeries,vectoresGraficas[0]);
        if(chart2!=-1) agregarCurvaAChart(chart2,nombreSeries,vectoresGraficas[1]);
        if(chart3!=-1) agregarCurvaAChart(chart3,nombreSeries,vectoresGraficas[2]);

        //Agrego las etiquetas a los ejes
//        vectorCharts[chart1]->agregarEtiquetas("Tiempo","Datos");
//        vectorCharts[chart2]->agregarEtiquetas("Tiempo","Datos");
//        vectorCharts[chart3]->agregarEtiquetas("Tiempo","Datos");

        //Temporal
        if(chart1!=-1) vectorCharts[chart1]->setAxisScale(WQ_Chart::xBottom, 0.0, 10.0);
    }
}

void WQ_Window::comparacionFuncionesProbabilidad()
{
    if(radioButtonSeleccionado!=2)
    {
        radioButtonSeleccionado=2;
        qDebug("Escogio comparacion por funciones probabilisticas");
        eliminarChart(0);
    }
}

void WQ_Window::comparacion3NombreTemporal()
{
    if(radioButtonSeleccionado!=3)
    {
        radioButtonSeleccionado=3;
        qDebug("Escogio comparacion por 3");
    }
}

void WQ_Window::salidaInformacion(QString mensaje)
{
    ui->plainTextEditConsole->appendPlainText(mensaje);
}

void WQ_Window::salidaError(QString mensaje)
{
    ui->plainTextEditConsole->appendPlainText("**** Error ****\n"+mensaje);
}
