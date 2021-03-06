#include "wq_analysing_widget.h"
#include "ui_wq_analysing_widget.h"

WQ_Analysing_Widget::WQ_Analysing_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WQ_Analysing_Widget)
{
    ui->setupUi(this);
    deshabilitarPorDatos(true);

    colorExpress = QColor(Qt::black);
    colorAdvanced = QColor(Qt::black);

    //Ocultar opciones pordefecto
    ocultarMostrarProbAuto(false);
    ocultarMostrarHvM(false);

    connect(ui->botonAddCurve,SIGNAL(clicked()),this,SLOT(agregarAnalisisManual()));
    connect(ui->botonTiempo,SIGNAL(clicked()),this, SLOT(agregarSeriesTiempoAutomatico()));
    connect(ui->botonCompleto,SIGNAL(clicked()),this,SLOT(agregarAnalisisCompletoAutomatico()));
    connect(ui->comboTipoAnalisis,SIGNAL(currentIndexChanged(int)),this,SLOT(cambioTipoAnalisis(int)));
    connect(ui->botonColorAdvanced,SIGNAL(clicked()),this,SLOT(cambiarColorAdvanced()));
    connect(ui->botonColorExpress,SIGNAL(clicked()),this,SLOT(cambiarColorExpress()));
}

WQ_Analysing_Widget::~WQ_Analysing_Widget()
{
    delete ui;
}

void WQ_Analysing_Widget::cambioTipoAnalisis(int tipoAnalisis)
{
    //Oculto todo
    ocultarMostrarTiempo(false);
    ocultarMostrarProbAuto(false);
    ocultarMostrarHvM(false);

    //Muestro lo correspondiente
    if(tipoAnalisis==0) ocultarMostrarTiempo(true);
    if(tipoAnalisis==1 || tipoAnalisis==2) ocultarMostrarProbAuto(true);
    if(tipoAnalisis==3) ocultarMostrarHvM(true);
}

void WQ_Analysing_Widget::ocultarMostrarTiempo(bool ocultar)
{
    ui->labelDuration->setVisible(ocultar);
    ui->labelStart->setVisible(ocultar);
    ui->spinDurationSegundos->setVisible(ocultar);
    ui->spinStartSegundos->setVisible(ocultar);
    ui->spinDurationMilis->setVisible(ocultar);
    ui->spinStartMilis->setVisible(ocultar);
    ui->spinDurationMicros->setVisible(ocultar);
    ui->spinStartMicros->setVisible(ocultar);
    ui->labelDurationSegundos->setVisible(ocultar);
    ui->labelStartSegundos->setVisible(ocultar);
    ui->labelDurationMilis->setVisible(ocultar);
    ui->labelStartMilis->setVisible(ocultar);
    ui->labelDurationMicros->setVisible(ocultar);
    ui->labelStartMicros->setVisible(ocultar);
}

void WQ_Analysing_Widget::ocultarMostrarProbAuto(bool ocultar)
{
    ui->checkBoxXLog->setVisible(ocultar);
    ui->checkBoxYLog->setVisible(ocultar);
}

void WQ_Analysing_Widget::ocultarMostrarHvM(bool ocultar)
{
    ui->checkBoxXLog->setVisible(ocultar);
    ui->checkBoxYLog->setVisible(ocultar);
    ui->labelM->setVisible(ocultar);
    ui->spinM->setVisible(ocultar);
}

void WQ_Analysing_Widget::agregarAnalisisManual()
{
    int inicio = ui->spinStartSegundos->value()*1000000 + ui->spinStartMilis->value()*1000 + ui->spinStartMicros->value();
    int fin = ui->spinDurationSegundos->value()*1000000 + ui->spinDurationMilis->value()*1000 + ui->spinDurationMicros->value() + inicio;
    int numDatos = ui->comboDatos->currentIndex();
    int numChart = ui->comboChart->currentIndex()==0? ui->comboChart->count()-1 : ui->comboChart->currentIndex()-1;
    int tipoAnalisis = ui->comboTipoAnalisis->currentIndex();
    bool remplazando = ui->checkBoxReplace->isChecked();
    bool xlog = ui->checkBoxXLog->isChecked();
    bool ylog = ui->checkBoxYLog->isChecked();
    int hlimit = ui->spinM->value();

    emit graficarUnaAnalisis(numDatos,tipoAnalisis,inicio,fin,numChart,remplazando, xlog, ylog, hlimit, colorAdvanced);
}

void WQ_Analysing_Widget::agregarSeriesTiempoAutomatico()
{
    int numDatos = ui->comboDatos->currentIndex();
    bool remplazando = ui->checkBoxReplaceEx->isChecked();

    emit graficarTodasSeriesTiempo(numDatos,remplazando, colorExpress);
}

void WQ_Analysing_Widget::agregarAnalisisCompletoAutomatico()
{
    int numDatos = ui->comboDatos->currentIndex();
    bool remplazando = ui->checkBoxReplaceEx->isChecked();

    emit graficarTodosLosAnalisis(numDatos,remplazando, colorExpress);
}

void WQ_Analysing_Widget::deshabilitarPorDatos(bool estado)
{
    //Analisis por tiempo
    ui->comboDatos->setDisabled(estado);
    ui->labelDuration->setDisabled(estado);
    ui->labelStart->setDisabled(estado);
    ui->spinDurationSegundos->setDisabled(estado);
    ui->spinStartSegundos->setDisabled(estado);
    ui->spinDurationMilis->setDisabled(estado);
    ui->spinStartMilis->setDisabled(estado);
    ui->spinDurationMicros->setDisabled(estado);
    ui->spinStartMicros->setDisabled(estado);
    ui->labelDurationSegundos->setDisabled(estado);
    ui->labelStartSegundos->setDisabled(estado);
    ui->labelDurationMilis->setDisabled(estado);
    ui->labelStartMilis->setDisabled(estado);
    ui->labelDurationMicros->setDisabled(estado);
    ui->labelStartMicros->setDisabled(estado);
    ui->comboChart->setDisabled(estado);
    ui->checkBoxReplace->setDisabled(estado);
    ui->checkBoxReplaceEx->setDisabled(estado);
    ui->botonTiempo->setDisabled(estado);
    ui->botonCompleto->setDisabled(estado);
    ui->botonAddCurve->setDisabled(estado);
    ui->comboTipoAnalisis->setDisabled(estado);
    ui->checkBoxXLog->setDisabled(estado);
    ui->checkBoxYLog->setDisabled(estado);
    ui->botonColorAdvanced->setDisabled(estado);
    ui->botonColorExpress->setDisabled(estado);
}

void WQ_Analysing_Widget::agregarDatos(QString nombreDatos)
{
    ui->comboDatos->addItem(nombreDatos);
    deshabilitarPorDatos(false);
}

void WQ_Analysing_Widget::eliminarDatos(int numDatos)
{
    ui->comboDatos->removeItem(numDatos);
    if(ui->comboDatos->count()==0) deshabilitarPorDatos(true);
}

void WQ_Analysing_Widget::agregarChart(QString nombreChart)
{
    ui->comboChart->addItem(nombreChart);
}

void WQ_Analysing_Widget::eliminarChart(int numChart)
{
    ui->comboChart->removeItem(numChart+1);
}

void WQ_Analysing_Widget::cambiarColorExpress()
{
    colorExpress = QColorDialog::getColor(QColor(Qt::white),this);
}

void WQ_Analysing_Widget::cambiarColorAdvanced()
{
    colorAdvanced = QColorDialog::getColor(QColor(Qt::white),this);
}
