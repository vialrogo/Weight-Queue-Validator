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

    spinDuration=new QSpinBox(this);
    spinDuration->setMaximum(60);
    spinDuration->setGeometry(70,120,55,30);
    spinDuration->setVisible(false);

    spinStart=new QSpinBox(this);
    spinStart->setMaximum(60);
    spinStart->setGeometry(70,85,55,30);
    spinStart->setVisible(false);

    comboDuration=new QComboBox(this);
    comboDuration->addItem("s");
    comboDuration->addItem("ms");
    comboDuration->addItem("us");
    comboDuration->setGeometry(125,120,45,30);
    comboDuration->setVisible(false);

    comboStart=new QComboBox(this);
    comboStart->addItem("s");
    comboStart->addItem("ms");
    comboStart->addItem("us");
    comboStart->setGeometry(125,85,45,30);
    comboStart->setVisible(false);

    comboChart=new QComboBox(this);
    comboChart->addItem("New Chart");
    comboChart->setGeometry(201,85,100,30);
    comboChart->setVisible(false);

    checkBoxReplace=new QCheckBox("Replace",this);
    checkBoxReplace->setGeometry(211,120,80,30);
    checkBoxReplace->setVisible(false);

    fuenteBotones = new QFont();
    fuenteBotones->setPointSize(12);
    fuenteBotones->setBold(true);

    botonAutomatic = new QPushButton(QIcon("Imagenes/Automatic1.png"),"Automatic",this);
    botonAutomatic->setIconSize(QSize(19,25));
    botonAutomatic->setFont(*fuenteBotones);
    botonAutomatic->setGeometry(22,160,120,35);
    botonAutomatic->setVisible(false);

    botonAddCurve = new QPushButton(QIcon("Imagenes/Add1.png"),"Add Curve",this);
    botonAddCurve->setIconSize(QSize(25,25));
    botonAddCurve->setFont(*fuenteBotones);
    botonAddCurve->setGeometry(166,160,120,35);
    botonAddCurve->setVisible(false);

    //Objetos data analysing

    //Objetos Comunes
    widgetDatos = new QWidget(this);
    widgetDatos->setMaximumSize(280,150);
    widgetDatos->setMinimumSize(280,150);
    widgetDatos->setGeometry(0,0,280,150);
    widgetDatos->setVisible(false);

    scrollArea = new QScrollArea(this);
    scrollArea->setMaximumSize(296,153);
    scrollArea->setMinimumSize(296,153);
    scrollArea->setGeometry(5,205,296,153);
    scrollArea->setWidget(widgetDatos);
    scrollArea->setVisible(false);

    deshabilitarPorDatos(true);
    configurarWidgetTiempo();

    connect(ui->radioButtonTiempo,SIGNAL(clicked()),this,SLOT(configurarWidgetTiempo()));
    connect(ui->radioButtonDatos,SIGNAL(clicked()),this,SLOT(configurarWidgetDatos()));
    connect(comboDuration,SIGNAL(currentIndexChanged(int)),this,SLOT(cambioComboDuration(int)));
    connect(comboStart,SIGNAL(currentIndexChanged(int)),this,SLOT(cambioComboStart(int)));
    connect(botonAddCurve,SIGNAL(clicked()),this,SLOT(agregarSerieTiempoManual()));
}

WQ_Analysing_Widget::~WQ_Analysing_Widget()
{
    delete ui;
}

void WQ_Analysing_Widget::agregarSerieTiempoManual()
{
    int escala = 1; //Valor en microsegundos
    if(comboStart->currentIndex()==1) escala=1000; //Valor en milisegundos
    if(comboStart->currentIndex()==0) escala=1000000; //Valor en milisegundos
    int inicio = spinStart->value() * escala;

    escala = 1; //Valor en microsegundos
    if(comboDuration->currentIndex()==1) escala=1000; //Valor en milisegundos
    if(comboDuration->currentIndex()==0) escala=1000000; //Valor en milisegundos

    int fin = (spinDuration->value() * escala) + inicio;

    int numDatos = comboDatos->currentIndex();

    qDebug("Va a graficar los datos %d, desde %d us hasta %d us", numDatos, inicio, fin);
}

void WQ_Analysing_Widget::configurarInterfaz(bool cual)
{
    //Analisis por tiempo
    comboDatos->setVisible(cual);
    labelDuration->setVisible(cual);
    labelStart->setVisible(cual);
    spinDuration->setVisible(cual);
    spinStart->setVisible(cual);
    comboDuration->setVisible(cual);
    comboStart->setVisible(cual);
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
    spinDuration->setDisabled(estado);
    spinStart->setDisabled(estado);
    comboDuration->setDisabled(estado);
    comboStart->setDisabled(estado);
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
    comboChart->removeItem(numChart);
}

void WQ_Analysing_Widget::cambioComboDuration(int indice)
{
    if(indice==0) spinDuration->setMaximum(60);
    else spinDuration->setMaximum(999);
}

void WQ_Analysing_Widget::cambioComboStart(int indice)
{
    if(indice==0) spinStart->setMaximum(60);
    else spinStart->setMaximum(999);
}


