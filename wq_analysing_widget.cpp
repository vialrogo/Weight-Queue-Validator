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
    labelDuration->setGeometry(5,85,60,30);
    labelDuration->setVisible(false);

    labelStart=new QLabel("Start",this);
    labelStart->setGeometry(5,120,60,30);
    labelStart->setVisible(false);

    spinDuration=new QSpinBox(this);
    spinDuration->setMaximum(999);
    spinDuration->setGeometry(70,85,55,30);
    spinDuration->setVisible(false);

    spinStart=new QSpinBox(this);
    spinStart->setMaximum(999);
    spinStart->setGeometry(70,120,55,30);
    spinStart->setVisible(false);

    comboDuration=new QComboBox(this);
    comboDuration->addItem("s");
    comboDuration->addItem("ms");
    comboDuration->addItem("us");
    comboDuration->setGeometry(125,85,45,30);
    comboDuration->setVisible(false);

    comboStart=new QComboBox(this);
    comboStart->addItem("s");
    comboStart->addItem("ms");
    comboStart->addItem("us");
    comboStart->setGeometry(125,120,45,30);
    comboStart->setVisible(false);

    comboChart=new QComboBox(this);
    comboChart->addItem("New Chart");
    comboChart->setGeometry(201,85,100,30);
    comboChart->setVisible(false);

    checkBoxReplace=new QCheckBox("Replace",this);
    checkBoxReplace->setGeometry(201,120,100,30);
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

    connect(ui->radioButtonTiempo,SIGNAL(clicked()),this,SLOT(configurarWidgetTiempo()));
    connect(ui->radioButtonDatos,SIGNAL(clicked()),this,SLOT(configurarWidgetDatos()));

    //Temporal
    comboDatos->addItem("Algo muy largo que solo sirve de ejemplo 1");
    comboDatos->addItem("Algo muy largo que solo sirve de ejemplo 2");
    comboDatos->addItem("Algo muy largo que solo sirve de ejemplo 3");
    comboChart->addItem("Chart 1");
    comboChart->addItem("Chart 2");
    comboChart->addItem("Chart 3");
}

WQ_Analysing_Widget::~WQ_Analysing_Widget()
{
    delete ui;
}

void WQ_Analysing_Widget::configurarInterfaz(bool cual)
{
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

void WQ_Analysing_Widget::configurarWidgetTiempo()
{
    configurarInterfaz(true);
}

void WQ_Analysing_Widget::configurarWidgetDatos()
{
    configurarInterfaz(false);
}


