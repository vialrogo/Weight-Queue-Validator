#include "wq_analysing_widget.h"
#include "ui_wq_analysing_widget.h"

WQ_Analysing_Widget::WQ_Analysing_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WQ_Analysing_Widget)
{
    ui->setupUi(this);

    //Objetos time view
    comboDatos = new QComboBox(this);
    comboDatos->setGeometry(5,48,296,30);
    comboDatos->setVisible(false);

    labelDuration=new QLabel("Duration",this);
    labelDuration->setGeometry(5,120,60,30);
    labelDuration->setVisible(false);

    labelStart=new QLabel("Start",this);
    labelStart->setGeometry(5,85,60,30);
    labelStart->setVisible(false);

    spinDurationSegundos=new QSpinBox(this);
    spinDurationSegundos->setMaximum(60);
    spinDurationSegundos->setGeometry(70,120,45,30);
    spinDurationSegundos->setVisible(false);

    spinStartSegundos=new QSpinBox(this);
    spinStartSegundos->setMaximum(59);
    spinStartSegundos->setGeometry(70,85,45,30);
    spinStartSegundos->setVisible(false);

    spinDurationMilis=new QSpinBox(this);
    spinDurationMilis->setMaximum(999);
    spinDurationMilis->setGeometry(140,120,55,30);
    spinDurationMilis->setVisible(false);

    spinStartMilis=new QSpinBox(this);
    spinStartMilis->setMaximum(999);
    spinStartMilis->setGeometry(140,85,55,30);
    spinStartMilis->setVisible(false);

    spinDurationMicros=new QSpinBox(this);
    spinDurationMicros->setMaximum(999);
    spinDurationMicros->setGeometry(220,120,55,30);
    spinDurationMicros->setVisible(false);

    spinStartMicros=new QSpinBox(this);
    spinStartMicros->setMaximum(999);
    spinStartMicros->setGeometry(220,85,55,30);
    spinStartMicros->setVisible(false);

    labelDurationSegundos = new QLabel("s",this);
    labelDurationSegundos->setGeometry(118,120,18,30);
    labelDurationSegundos->setVisible(false);

    labelStartSegundos = new QLabel("s",this);
    labelStartSegundos->setGeometry(118,85,18,30);
    labelStartSegundos->setVisible(false);

    labelDurationMilis = new QLabel("ms",this);
    labelDurationMilis->setGeometry(198,120,18,30);
    labelDurationMilis->setVisible(false);

    labelStartMilis = new QLabel("ms",this);
    labelStartMilis->setGeometry(198,85,18,30);
    labelStartMilis->setVisible(false);

    labelDurationMicros = new QLabel("us",this);
    labelDurationMicros->setGeometry(278,120,18,30);
    labelDurationMicros->setVisible(false);

    labelStartMicros = new QLabel("us",this);
    labelStartMicros->setGeometry(278,85,18,30);
    labelStartMicros->setVisible(false);

    comboChart=new QComboBox(this);
    comboChart->addItem("New Chart");
    comboChart->setGeometry(5,158,180,28);
    comboChart->setVisible(false);

    checkBoxReplace=new QCheckBox("Replace",this);
    checkBoxReplace->setGeometry(200,157,80,30);
    checkBoxReplace->setVisible(false);

    fuenteBotones = new QFont();
    fuenteBotones->setPointSize(12);
    fuenteBotones->setBold(true);

    botonAutomatic = new QPushButton(QIcon("Imagenes/Automatic1.png"),"Automatic",this);
    botonAutomatic->setIconSize(QSize(19,25));
    botonAutomatic->setFont(*fuenteBotones);
    botonAutomatic->setGeometry(22,202,120,35);
    botonAutomatic->setVisible(false);

    botonAddCurve = new QPushButton(QIcon("Imagenes/Add1.png"),"Add Curve",this);
    botonAddCurve->setIconSize(QSize(25,25));
    botonAddCurve->setFont(*fuenteBotones);
    botonAddCurve->setGeometry(166,202,120,35);
    botonAddCurve->setVisible(false);

    //Objetos data analysing

    //Objetos Comunes
    widgetDatos = new QWidget(this);
    widgetDatos->setMaximumSize(280,110);
    widgetDatos->setMinimumSize(280,110);
    widgetDatos->setGeometry(0,0,280,110);
    widgetDatos->setVisible(false);

    scrollArea = new QScrollArea(this);
    scrollArea->setMaximumSize(296,113);
    scrollArea->setMinimumSize(296,113);
    scrollArea->setGeometry(5,245,296,113);
    scrollArea->setWidget(widgetDatos);
    scrollArea->setVisible(false);

    deshabilitarPorDatos(true);
    configurarWidgetTiempo();

    connect(ui->radioButtonTiempo,SIGNAL(clicked()),this,SLOT(configurarWidgetTiempo()));
    connect(ui->radioButtonDatos,SIGNAL(clicked()),this,SLOT(configurarWidgetDatos()));
    connect(botonAddCurve,SIGNAL(clicked()),this,SLOT(agregarSerieTiempoManual()));
    connect(botonAutomatic,SIGNAL(clicked()),this, SLOT(agregarSerieTiempoAutomatico()));
}

WQ_Analysing_Widget::~WQ_Analysing_Widget()
{
    delete ui;
}

void WQ_Analysing_Widget::agregarSerieTiempoManual()
{
    int inicio = spinStartSegundos->value()*1000000 + spinStartMilis->value()*1000 + spinStartMicros->value();
    int fin = spinDurationSegundos->value()*1000000 + spinDurationMilis->value()*1000 + spinDurationMicros->value() + inicio;
    int numDatos = comboDatos->currentIndex();
    int numChart = comboChart->currentIndex()==0? comboChart->count()-1 : comboChart->currentIndex()-1;
    bool remplazando = checkBoxReplace->isChecked();

    emit graficarUnaSerieTiempo(numDatos,inicio,fin,numChart,remplazando);
}

void WQ_Analysing_Widget::agregarSerieTiempoAutomatico()
{
    int numDatos = comboDatos->currentIndex();
    bool remplazando = checkBoxReplace->isChecked();

    emit graficarTodasSeriesTiempo(numDatos,remplazando);
}

void WQ_Analysing_Widget::configurarInterfaz(bool cual)
{
    //Analisis por tiempo
    comboDatos->setVisible(cual);
    labelDuration->setVisible(cual);
    labelStart->setVisible(cual);
    spinDurationSegundos->setVisible(cual);
    spinStartSegundos->setVisible(cual);
    spinDurationMilis->setVisible(cual);
    spinStartMilis->setVisible(cual);
    spinDurationMicros->setVisible(cual);
    spinStartMicros->setVisible(cual);
    labelDurationSegundos->setVisible(cual);
    labelStartSegundos->setVisible(cual);
    labelDurationMilis->setVisible(cual);
    labelStartMilis->setVisible(cual);
    labelDurationMicros->setVisible(cual);
    labelStartMicros->setVisible(cual);
    comboChart->setVisible(cual);
    checkBoxReplace->setVisible(cual);
    botonAutomatic->setVisible(cual);
    botonAddCurve->setVisible(cual);

    //Objetos comunes
    scrollArea->setVisible(true);
    widgetDatos->setVisible(true);
}

void WQ_Analysing_Widget::deshabilitarPorDatos(bool estado)
{
    //Analisis por tiempo
    comboDatos->setDisabled(estado);
    labelDuration->setDisabled(estado);
    labelStart->setDisabled(estado);
    spinDurationSegundos->setDisabled(estado);
    spinStartSegundos->setDisabled(estado);
    spinDurationMilis->setDisabled(estado);
    spinStartMilis->setDisabled(estado);
    spinDurationMicros->setDisabled(estado);
    spinStartMicros->setDisabled(estado);
    labelDurationSegundos->setDisabled(estado);
    labelStartSegundos->setDisabled(estado);
    labelDurationMilis->setDisabled(estado);
    labelStartMilis->setDisabled(estado);
    labelDurationMicros->setDisabled(estado);
    labelStartMicros->setDisabled(estado);
    comboChart->setDisabled(estado);
    checkBoxReplace->setDisabled(estado);
    botonAutomatic->setDisabled(estado);
    botonAddCurve->setDisabled(estado);
}

void WQ_Analysing_Widget::configurarWidgetTiempo()
{
    configurarInterfaz(true);
}

void WQ_Analysing_Widget::configurarWidgetDatos()
{
    configurarInterfaz(false);
}

void WQ_Analysing_Widget::agregarDatos(QString nombreDatos)
{
    comboDatos->addItem(nombreDatos);
    deshabilitarPorDatos(false);
}

void WQ_Analysing_Widget::eliminarDatos(int numDatos)
{
    comboDatos->removeItem(numDatos);
    if(comboDatos->count()==0) deshabilitarPorDatos(true);
}

void WQ_Analysing_Widget::agregarChart(QString nombreChart)
{
    comboChart->addItem(nombreChart);
}

void WQ_Analysing_Widget::eliminarChart(int numChart)
{
    comboChart->removeItem(numChart+1);
}
