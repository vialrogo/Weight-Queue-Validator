#include "wq_window.h"

WQ_Window::WQ_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WQ_Window)
{
    ui->setupUi(this);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    tamanoEstandarGrafico= QSize(330,200);
    numeroWidgetsUsados=0;
    validador = new WQ_Validator();
    arregoWidgets = new QWidget*[6];
    vectorCharts = new QVector<WQ_Chart*>();
    vectorChartWidgets = new QVector<WQ_Chart_Widget*>();
    ioFiles = new WQ_IOFiles(this);
    ventanaPreferencias = new WQ_Window_Preferences(this);
    widgetNewChart = new WQ_Analysing_Widget(ui->widgetTabNew);

    //Agrego y acomodo los widgets de los charts
    for (int i = 0; i < 6; ++i) {
        arregoWidgets[i]=new QWidget(this);
        colocarWidgetEnPosicion(i,i);
        agregarQuitarBordeWidgets(i,true);
    }

    //Configuraciones de apariencia area (consola)
    QPalette p = ui->plainTextEditConsole->palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::white);
    ui->plainTextEditConsole->setPalette(p);

    //Agregar toolboox
    toolBoxCharts = new QToolBox(ui->widgetTabCurrent);
    toolBoxCharts->setGeometry(0,0,310,362);
    toolBoxCharts->setVisible(true);

    //Agrego el widget de los archivos
    widgetFiles = new WQ_Data_Widget(ui->widgetTabData);
    widgetFiles->setGeometry(-1,70,308,294);
    widgetFiles->setVisible(true);

    //Agrego el widget de los nuevos chart
    widgetNewChart->setGeometry(0,0,306,363);
    widgetNewChart->setVisible(true);

    connect(ui->pushButtonLoadFile,SIGNAL(clicked()),this,SLOT(cargarArchivo()));
    connect(ui->pushButtonLoadOthers,SIGNAL(clicked()),this,SLOT(cargarOtrosArchivos()));
    connect(widgetFiles,SIGNAL(eliminarFileDataWidget(int)),ioFiles,SLOT(elimiarArchivo(int)));
    connect(ioFiles,SIGNAL(archivoCargado(QString, short*)),this,SLOT(archivoCargadoExitoamente(QString, short*)));
    connect(ioFiles,SIGNAL(archivoNoCargado(QString)),this,SLOT(noSePudoCargarArchivo(QString)));
    connect(ioFiles,SIGNAL(archivoEliminado(int)),widgetNewChart,SLOT(eliminarDatos(int)));
    connect(widgetNewChart,SIGNAL(graficarUnaSerieTiempo(int,int,int,int,bool)),this,SLOT(agregarSerieDeTiempo(int,int,int,int,bool)));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(acercaDe()));
    connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->actionPreferences,SIGNAL(triggered()),ventanaPreferencias,SLOT(show()));
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

        //Creo y agrego el chart widget
        WQ_Chart_Widget* chartWidget = new WQ_Chart_Widget(this,vectorChartWidgets->size());
        toolBoxCharts->addItem(chartWidget,nombreChart);
        vectorChartWidgets->push_back(chartWidget);

        //Hago los connect
        connect(chartWidget,SIGNAL(eliminarChart(int)),this,SLOT(eliminarChart(int)));
        connect(chartWidget,SIGNAL(mostrarOcultarCurvaChart(int,bool)),nuevoChart,SLOT(mostrarOcultarCurva(int,bool)));
        connect(chartWidget,SIGNAL(eliminarCurvaChart(int)),nuevoChart,SLOT(elimiarCurvaPlot(int)));
        connect(chartWidget,SIGNAL(cambiarColorCurvaChart(int,QColor)),nuevoChart,SLOT(cambiarColorCuva(int,QColor)));
        connect(chartWidget,SIGNAL(cambiarScrollX(bool)),nuevoChart,SLOT(desHabilitarXScroll(bool)));
        connect(chartWidget,SIGNAL(cambiarScrollY(bool)),nuevoChart,SLOT(desHabilitarYScroll(bool)));

        //Actualizar el tamaño de todos los chartWidgets
        int numChartWidgets = vectorChartWidgets->size();
        for (int i = 0; i < numChartWidgets; ++i)
            vectorChartWidgets->at(i)->cambiarGeometriaNumeroCharts(numChartWidgets);

        //Otros
        numeroWidgetsUsados++;
        widgetNewChart->agregarChart(nombreChart); //Agrego el chart al comboBox en Analysing_Widget
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
        //Actualizo los QWidgets contenedores de los Charts
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

        //Actualizar el tamaño de todos los chartWidgets
        int numChartWidgets = vectorChartWidgets->size();
        for (int i = 0; i < numChartWidgets; ++i)
            vectorChartWidgets->at(i)->cambiarGeometriaNumeroCharts(numChartWidgets);

        //Elimino el chart al comboBox en Analysing_Widget
        widgetNewChart->eliminarChart(numChart);

        //Acomodo el último widget
        agregarQuitarBordeWidgets(numeroWidgetsUsados-1, true);
        numeroWidgetsUsados--;

        salidaInformacion("Chart eliminado exitosamente");
    }
    else
    {
        salidaError("Intentó quitar un chart y no existe");
    }
}

void WQ_Window::agregarCurvaAChart(int numChart, QString nombreCurva, QVector<QPointF> *datos)
{
    vectorCharts->at(numChart)->agregarCurva(datos);
    vectorChartWidgets->at(numChart)->agregarCurva(nombreCurva);
}

void WQ_Window::agregarSerieDeTiempo(int numDatos, int inicio, int fin, int numChart, bool remplazar)
{
    QVector<QPointF>* vectorDatos = validador->obtenerVectorDatos(numDatos,inicio,fin);
//    QString nombreChart = "Serie Datos "+numDatos+" de "+inicio+" a "+fin;
    int chart1 = agregarChart("??");
    if(chart1!=-1)
    {
//        QString nombreChart = "Serie  de "+inicio+" a "+fin;
        agregarCurvaAChart(chart1,"??",vectorDatos);
        vectorCharts->at(chart1)->setAxisScale(WQ_Chart::xBottom, 0.0, 10.0);
    }
}

void WQ_Window::cargarArchivo()
{
    QString rutaArchivo = ui->lineEditLoadFile->text();

    if (!rutaArchivo.isEmpty())
        ioFiles->agregarArchivo(rutaArchivo);
}

void WQ_Window::archivoCargadoExitoamente(QString rutaArchivo, short* datos)
{
    QString nombreArchivo = rutaArchivo.right(rutaArchivo.size()-rutaArchivo.lastIndexOf("/")-1);
    widgetFiles->agregarArchivo(nombreArchivo);
    widgetNewChart->agregarDatos(nombreArchivo);
    validador->agregarDatos(datos);
    salidaInformacion("Carga completa del archivo "+nombreArchivo);
}

void WQ_Window::noSePudoCargarArchivo(QString rutaArchivo)
{
    QString nombreArchivo = rutaArchivo.right(rutaArchivo.size()-rutaArchivo.lastIndexOf("/")-1);
    salidaError("Imposible cargar el archivo "+nombreArchivo);
}

void WQ_Window::cargarOtrosArchivos()
{
    QString nombreArchivo = QFileDialog::getOpenFileName(this, "Load times file", "./Datos", "Time data (*.times);;All Files (*)");
    ui->lineEditLoadFile->setText(nombreArchivo);
}

void WQ_Window::salidaInformacion(QString mensaje)
{
    ui->plainTextEditConsole->appendHtml("<span style=\"color:green\">-> "+mensaje+"</span>");
}

void WQ_Window::salidaError(QString mensaje)
{
    ui->plainTextEditConsole->appendHtml("<span style=\"color:red\">-> Error: "+mensaje+"</span>");
}
