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
    vectorCharts = new QVector<WQ_Chart*>();
    vectorChartWidgets = new QVector<WQ_Chart_Widget*>();

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
    toolBoxCharts = new QToolBox(ui->tabExistente);
    toolBoxCharts->setGeometry(0,0,310,362);
    toolBoxCharts->setVisible(true);

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

int WQ_Window::agregarChart(QString nombreChart)
{
    if(numeroWidgetsUsados<6)
    {
        agregarQuitarBordeWidgets(numeroWidgetsUsados,false);

        //Creo y agrego el chart
        WQ_Chart* nuevoChart = new WQ_Chart(arregoWidgets[numeroWidgetsUsados], tamanoEstandarGrafico);
        vectorCharts->push_back(nuevoChart);
        nuevoChart->setVisible(true);

        //Creo y agrego su vector de curvas
        QVector<QVector<QPointF>* >* vectorCurvas = new QVector <QVector<QPointF>* > ();
        vectorCurvasPorChart->push_back(vectorCurvas);

        //Agrego el chart widget
        WQ_Chart_Widget* chartWidget = new WQ_Chart_Widget(this,vectorChartWidgets->size());
        toolBoxCharts->addItem(chartWidget,nombreChart);
        connect(chartWidget,SIGNAL(eliminarChart(int)),this,SLOT(eliminarChart(int)));
        vectorChartWidgets->push_back(chartWidget);

        //Actualizar el tamaño de todos los chartWidgets
        int numChartWidgets = vectorChartWidgets->size();
        for (int i = 0; i < numChartWidgets; ++i) {
            vectorChartWidgets->at(i)->cambiarGeometriaNumeroCharts(numChartWidgets);
        }

        //Otros
        numeroWidgetsUsados++;
        salidaInformacion("Chart agregado exitosamente");
        return vectorCharts->size()-1;
    }
    else
    {
        salidaError("Intentó agregar un chart y no cabe");
        return -1;
    }
}

void WQ_Window::eliminarChart(int numChart)
{
    if(vectorCharts->size()>numChart)
    {
        QWidget* temporal;

        for (int i = numChart+1; i < vectorCharts->size(); ++i)
        {
            //Cambio la posición de los widgets en la interfaz
            colocarWidgetEnPosicion(i,i-1);
            colocarWidgetEnPosicion(i-1,i);

            //Troco los widgets en el arreglo
            temporal=arregoWidgets[i-1];
            arregoWidgets[i-1] = arregoWidgets[i];
            arregoWidgets[i]=temporal;

            //Actualizo los valores de los ChartWidget
            vectorChartWidgets->at(i)->setNumChart(vectorChartWidgets->at(i)->getNumChart()-1);
        }

        //Elimino el Chart
        delete vectorCharts->at(numChart);
        vectorCharts->remove(numChart);

        //Elimino el ChartWidget
        toolBoxCharts->removeItem(toolBoxCharts->indexOf(vectorChartWidgets->at(numChart)));
        delete vectorChartWidgets->at(numChart);
        vectorChartWidgets->remove(numChart);

        //Elimino todas las curvas del chart
        for (int i = 0; i < vectorCurvasPorChart->at(numChart)->size(); ++i) {
            delete vectorCurvasPorChart->at(numChart)->at(0);
            vectorCurvasPorChart->at(numChart)->remove(0);
        }
        delete vectorCurvasPorChart->at(numChart);
        vectorCurvasPorChart->remove(numChart);

        //Actualizar el tamaño de todos los chartWidgets
        int numChartWidgets = vectorChartWidgets->size();
        for (int i = 0; i < numChartWidgets; ++i) {
            vectorChartWidgets->at(i)->cambiarGeometriaNumeroCharts(numChartWidgets);
        }

        //Acomodo el último widget
        agregarQuitarBordeWidgets(numeroWidgetsUsados-1, true);
        numeroWidgetsUsados--;
    }
    else
    {
        salidaError("Intentó quitar un chart y no existe");
    }
}

void WQ_Window::agregarCurvaAChart(int numChart, QString nombreCurva, QVector<QPointF> *datos)
{
    QVector<QVector<QPointF>* >* vectorCurvas = vectorCurvasPorChart->at(numChart);
    vectorCurvas->push_back(datos);
    vectorCharts->at(numChart)->agregarCurva(datos);
    vectorChartWidgets->at(numChart)->agregarCurva(nombreCurva);
}

void WQ_Window::comparacionEscalasDeTiempo()
{
    if(radioButtonSeleccionado!=1) //Esto hay que hacerlo dinámico
    {
        radioButtonSeleccionado=1;
        QVector<QPointF>** vectoresGraficas = validador->comparacionEscalasDeTiempo();

        //Quito los punteados, defino los gráficos que se van a dibujar y hago que las gráficas se vean
        int chart1 = agregarChart("Grafica 1");
        int chart2 = agregarChart("Grafica 2");
        int chart3 = agregarChart("Grafica 3");

        //Creo las curvas que voy a pintar y la serie que corresponde
        if(chart1!=-1) agregarCurvaAChart(chart1,"Serie De Tiempo 1",vectoresGraficas[0]);
//        if(chart1!=-1) agregarCurvaAChart(chart1,"Serie De Tiempo 2",vectoresGraficas[1]);
//        if(chart1!=-1) agregarCurvaAChart(chart1,"Serie De Tiempo 3",vectoresGraficas[2]);
        if(chart2!=-1) agregarCurvaAChart(chart2,"Serie De Tiempo 2",vectoresGraficas[1]);
        if(chart3!=-1) agregarCurvaAChart(chart3,"Serie De Tiempo 3",vectoresGraficas[2]);

        //Agrego las etiquetas a los ejes
//        vectorCharts[chart1]->agregarEtiquetas("Tiempo","Datos");
//        vectorCharts[chart2]->agregarEtiquetas("Tiempo","Datos");
//        vectorCharts[chart3]->agregarEtiquetas("Tiempo","Datos");

        //Temporal
        if(chart1!=-1) vectorCharts->at(chart1)->setAxisScale(WQ_Chart::xBottom, 0.0, 10.0);
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
