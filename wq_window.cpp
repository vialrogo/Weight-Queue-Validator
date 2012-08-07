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
    widgetNewChart = new WQ_Analysing_Widget(ui->widgetTabNew);
    genPoisson = new WQ_Gen_Poisson(this);
    genHeavyTail = new WQ_Gen_HeavyTail(this);

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
    widgetFiles->setGeometry(-1,160,308,204);
    widgetFiles->setVisible(true);

    //Agrego el widget de los nuevos chart
    widgetNewChart->setGeometry(0,0,306,363);
    widgetNewChart->setVisible(true);

    connect(ui->pushButtonLoadFile,SIGNAL(clicked()),this,SLOT(cargarArchivo()));
    connect(ui->pushButtonLoadOthers,SIGNAL(clicked()),this,SLOT(cargarOtrosArchivos()));
    connect(widgetFiles,SIGNAL(eliminarFileDataWidget(int)),ioFiles,SLOT(elimiarArchivo(int)));
    connect(ioFiles,SIGNAL(archivoCargado(QString, short*)),this,SLOT(archivoCargadoExitosamente(QString, short*)));
    connect(ioFiles,SIGNAL(archivoNoCargado(QString)),this,SLOT(noSePudoCargarArchivo(QString)));
    connect(ioFiles,SIGNAL(archivoEliminado(int)),widgetNewChart,SLOT(eliminarDatos(int)));
    connect(widgetNewChart,SIGNAL(graficarUnaAnalisis(int,int,int,int,int,bool,bool,bool,int,QColor)),this,SLOT(agregarUnAnalisis(int,int,int,int,int,bool,bool,bool,int,QColor)));
    connect(widgetNewChart,SIGNAL(graficarTodasSeriesTiempo(int,bool,QColor)),this,SLOT(agregarTodasLasSeriesDeTiempo(int,bool,QColor)));
    connect(widgetNewChart,SIGNAL(graficarTodosLosAnalisis(int,bool,QColor)),this,SLOT(agregarTodosLosAnalisis(int,bool,QColor)));
    connect(ui->comboBoxGeneradas, SIGNAL(currentIndexChanged(int)),this,SLOT(cambiarEqiquetaGeneradas(int)));
    connect(ui->pushButtonLoadSintetic,SIGNAL(clicked()),this,SLOT(crearDatosSinteticos()));
    connect(genPoisson,SIGNAL(datosGeneradosExitosamente(QString,short*)),this,SLOT(datosGeneradosExitosamente(QString,short*)));
    connect(genHeavyTail,SIGNAL(datosGeneradosExitosamente(QString,short*)),this,SLOT(datosGeneradosExitosamente(QString,short*)));
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

void WQ_Window::agregarUnAnalisis(int numDatos, int numAnalisis, int inicio, int fin, int numChart, bool remplazar, bool xlog, bool ylog, int hlimit, QColor colorGrafica)
{
    QVector<QPointF>* vectorDatos = validador->obtenerVectorDatos(numDatos,numAnalisis,inicio,fin,hlimit);

    if(remplazar && numChart<vectorCharts->size())
    {
        int numCurvasViejas = vectorChartWidgets->at(numChart)->getNumeroCurvas();
        for (int i = 0; i < numCurvasViejas; ++i) vectorChartWidgets->at(numChart)->eliminarCurvaChartWidget(0);
        agregarCurvaAChart(numChart,QString::number(numDatos)+". Serie de "+QString::number(inicio)+"us a "+QString::number(fin)+"us",vectorDatos);
    }
    else
    {
        if(numChart==vectorCharts->size()) agregarChart("Serie de Datos "+QString::number(numDatos));
        if(numChart<6) agregarCurvaAChart(numChart,QString::number(numDatos)+". Serie de "+QString::number(inicio)+"us a "+QString::number(fin)+"us",vectorDatos);
    }
    vectorCharts->at(numChart)->escalaLogEjeX(xlog);
    vectorCharts->at(numChart)->escalaLogEjeY(ylog);
    vectorCharts->at(numChart)->cambiarColorCuva(vectorChartWidgets->at(numChart)->getNumeroCurvas()-1,colorGrafica);
}

void WQ_Window::agregarTodasLasSeriesDeTiempo(int numDatos, bool remplazar, QColor colorGrafica)
{
    QTime midnight(0, 0, 0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    int inicio=0;

    //Si es el caso, elimino todos los charts
    while (vectorCharts->size()>0 && remplazar==true) eliminarChart(0);

    //Primer gráfico: 1 minuto
    QVector<QPointF>* vectorDatos0 = validador->obtenerVectorDatos(numDatos,0,0,60000000,1);
    if(vectorCharts->size()<1) agregarChart("Serie de Datos en Chart "+QString::number(numDatos));
    agregarCurvaAChart(0,QString::number(numDatos)+". 0us a 60000000us",vectorDatos0);
    vectorCharts->at(0)->cambiarColorCuva(vectorChartWidgets->at(0)->getNumeroCurvas()-1,colorGrafica);

    //Segundo gráfico: 10 segundo
    inicio = qrand()%(60000000-10000000);
    QVector<QPointF>* vectorDatos1 = validador->obtenerVectorDatos(numDatos,0,inicio,inicio+10000000,1);
    if(vectorCharts->size()<2) agregarChart("Serie de Datos en Chart "+QString::number(numDatos));
    agregarCurvaAChart(1,QString::number(numDatos)+". "+QString::number(inicio)+"us a "+QString::number(inicio+10000000)+"us",vectorDatos1);
    vectorCharts->at(1)->cambiarColorCuva(vectorChartWidgets->at(1)->getNumeroCurvas()-1,colorGrafica);

    //Tercer gráfico: 1 segundo
    inicio = qrand()%(60000000-1000000);
    QVector<QPointF>* vectorDatos2 = validador->obtenerVectorDatos(numDatos,0,inicio,inicio+1000000,1);
    if(vectorCharts->size()<3) agregarChart("Serie de Datos en Chart "+QString::number(numDatos));
    agregarCurvaAChart(2,QString::number(numDatos)+". "+QString::number(inicio)+"us a "+QString::number(inicio+1000000)+"us",vectorDatos2);
    vectorCharts->at(2)->cambiarColorCuva(vectorChartWidgets->at(2)->getNumeroCurvas()-1,colorGrafica);

    //Cuarto gráfico: 100 milisegundos
    inicio = qrand()%(60000000-100000);
    QVector<QPointF>* vectorDatos3 = validador->obtenerVectorDatos(numDatos,0,inicio,inicio+100000,1);
    if(vectorCharts->size()<4) agregarChart("Serie de Datos en Chart "+QString::number(numDatos));
    agregarCurvaAChart(3,QString::number(numDatos)+". "+QString::number(inicio)+"us a "+QString::number(inicio+100000)+"us",vectorDatos3);
    vectorCharts->at(3)->cambiarColorCuva(vectorChartWidgets->at(3)->getNumeroCurvas()-1,colorGrafica);

    //Quinto gráfico: 10 milisegundos
    inicio = qrand()%(60000000-10000);
    QVector<QPointF>* vectorDatos4 = validador->obtenerVectorDatos(numDatos,0,inicio,inicio+10000,1);
    if(vectorCharts->size()<5) agregarChart("Serie de Datos en Chart "+QString::number(numDatos));
    agregarCurvaAChart(4,QString::number(numDatos)+". "+QString::number(inicio)+"us a "+QString::number(inicio+10000)+"us",vectorDatos4);
    vectorCharts->at(4)->cambiarColorCuva(vectorChartWidgets->at(4)->getNumeroCurvas()-1,colorGrafica);

    //Sexto gráfico: 1 milisegundo
    inicio = qrand()%(60000000-1000);
    QVector<QPointF>* vectorDatos5 = validador->obtenerVectorDatos(numDatos,0,inicio,inicio+1000,1);
    if(vectorCharts->size()<6) agregarChart("Serie de Datos en Chart "+QString::number(numDatos));
    agregarCurvaAChart(5,QString::number(numDatos)+". "+QString::number(inicio)+"us a "+QString::number(inicio+1000)+"us",vectorDatos5);
    vectorCharts->at(5)->cambiarColorCuva(vectorChartWidgets->at(5)->getNumeroCurvas()-1,colorGrafica);
}

void WQ_Window::agregarTodosLosAnalisis(int numDatos, bool remplazar, QColor colorGrafica)
{
    //Si es el caso, elimino todos los charts
    while (vectorCharts->size()>0 && remplazar==true) eliminarChart(0);

    //Primer gráfico: Tiempo
    QVector<QPointF>* vectorDatos0 = validador->obtenerVectorDatos(numDatos,0,0,60000000,1);
    if(vectorCharts->size()<1) agregarChart("Serie de Tiempo");
    agregarCurvaAChart(0,QString::number(numDatos)+". 0us a 60000000us",vectorDatos0);
    vectorCharts->at(0)->cambiarColorCuva(vectorChartWidgets->at(0)->getNumeroCurvas()-1,colorGrafica);

    //Primer gráfico: Probabilidad
    QVector<QPointF>* vectorDatos1 = validador->obtenerVectorDatos(numDatos,1,0,60000000,1);
    if(vectorCharts->size()<2) agregarChart("Probabilidad");
    agregarCurvaAChart(1,QString::number(numDatos)+". Probabilidad",vectorDatos1);
    vectorCharts->at(1)->cambiarColorCuva(vectorChartWidgets->at(1)->getNumeroCurvas()-1,colorGrafica);

    //Primer gráfico: Probabilidad Log
    QVector<QPointF>* vectorDatos2 = validador->obtenerVectorDatos(numDatos,1,0,60000000,1);
    if(vectorCharts->size()<3) agregarChart("Probabilidad Log-Log");
    agregarCurvaAChart(2,QString::number(numDatos)+". Probabilidad log-log",vectorDatos2);
    vectorCharts->at(2)->escalaLogEjeX(true);
    vectorCharts->at(2)->escalaLogEjeY(true);
    vectorCharts->at(2)->cambiarColorCuva(vectorChartWidgets->at(2)->getNumeroCurvas()-1,colorGrafica);

    //Primer gráfico: Autocorrelacion
    QVector<QPointF>* vectorDatos3 = validador->obtenerVectorDatos(numDatos,2,0,60000000,1);
    if(vectorCharts->size()<4) agregarChart("Autocorrelacion");
    agregarCurvaAChart(3,QString::number(numDatos)+". Autocorrelacion",vectorDatos3);
    vectorCharts->at(3)->cambiarColorCuva(vectorChartWidgets->at(3)->getNumeroCurvas()-1,colorGrafica);

    //Primer gráfico: Autocorrelacion Log
    QVector<QPointF>* vectorDatos4 = validador->obtenerVectorDatos(numDatos,2,0,60000000,1);
    if(vectorCharts->size()<5) agregarChart("Autocorrelacion Log-Log");
    agregarCurvaAChart(4,QString::number(numDatos)+". Autocorrelacion log-log",vectorDatos4);
    vectorCharts->at(4)->escalaLogEjeX(true);
    vectorCharts->at(4)->escalaLogEjeY(true);
    vectorCharts->at(4)->cambiarColorCuva(vectorChartWidgets->at(4)->getNumeroCurvas()-1,colorGrafica);

    //Primer gráfico: H vs M
    QVector<QPointF>* vectorDatos5 = validador->obtenerVectorDatos(numDatos,3,0,60000000,10);
    if(vectorCharts->size()<6) agregarChart("H vs. M");
    agregarCurvaAChart(5,QString::number(numDatos)+". H vs. M",vectorDatos5);
    vectorCharts->at(5)->escalaLogEjeX(true);
    vectorCharts->at(5)->cambiarColorCuva(vectorChartWidgets->at(5)->getNumeroCurvas()-1,colorGrafica);
}

void WQ_Window::crearDatosSinteticos()
{
    int opcion = ui->comboBoxGeneradas->currentIndex();
    double parametro = ui->spinParametro->value();

    if(opcion==0) genPoisson->generarDatosSinteticos(parametro);
    else genHeavyTail->generarDatosSinteticos(parametro,1.0,1000); /// Beta, alfa, escala, Datos quemados, sacar de aquí!!
}

void WQ_Window::cargarArchivo()
{
    QString rutaArchivo = ui->lineEditLoadFile->text();

    if (!rutaArchivo.isEmpty())
        ioFiles->agregarArchivo(rutaArchivo);
}

void WQ_Window::datosGeneradosExitosamente(QString nombreDatos, short *datos)
{
    widgetFiles->agregarArchivo(nombreDatos);
    widgetNewChart->agregarDatos(nombreDatos);
    ioFiles->agregarDatosSinteticos(nombreDatos, datos);
    validador->agregarDatos(datos);
    salidaInformacion("Generación completa de datos "+nombreDatos);
}

void WQ_Window::archivoCargadoExitosamente(QString rutaArchivo, short* datos)
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

void WQ_Window::cambiarEqiquetaGeneradas(int opcion)
{
    if(opcion==0) ui->labelGeneradas->setText("λ:");
    else  ui->labelGeneradas->setText("β:");
}
