#ifndef WQ_WINDOW_H
#define WQ_WINDOW_H

#include <QMessageBox>
#include <QMainWindow>
#include <QTextCodec>
#include <QToolBox>
#include <QFileDialog>
#include "ui_wq_window.h"
#include "wq_chart.h"
#include "wq_validator.h"
#include "wq_chart_widget.h"
#include "wq_data_widget.h"
#include "wq_iofiles.h"
#include "wq_window_preferences.h"
#include "wq_analysing_widget.h"

namespace Ui {
    class WQ_Window;
}

class WQ_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit WQ_Window(QWidget *parent = 0);
    ~WQ_Window();

private:
    Ui::WQ_Window *ui;
    int radioButtonSeleccionado;
    int numeroWidgetsUsados;
    QSize tamanoEstandarGrafico;
    WQ_Validator* validador;
    QWidget** arregoWidgets;
    QVector<WQ_Chart*>* vectorCharts;
    QVector<WQ_Chart_Widget*>* vectorChartWidgets;
    QToolBox* toolBoxCharts;
    WQ_Data_Widget* widgetFiles;
    WQ_IOFiles* ioFiles;
    WQ_Window_Preferences* ventanaPreferencias;
    WQ_Analysing_Widget* widgetNewChart;

    void agregarQuitarBordeWidgets(int numWidget, bool bordeBool);
    int agregarChart(QString nombreChart);
    void colocarWidgetEnPosicion(int numWidget, int posicion);
    void agregarCurvaAChart(int numChart, QString nombreCurva, QVector<QPointF>* datos);
    void salidaInformacion(QString mensaje);
    void salidaError(QString mensaje);

private slots:
    void acercaDe();
    void analizarDatos();
    void simularDatos();
    void eliminarChart(int numChart);
    void cargarArchivo();
    void cargarOtrosArchivos();
    void archivoCargadoExitoamente(QString rutaArchivo);
    void noSePudoCargarArchivo(QString rutaArchivo);
};

#endif // WQ_WINDOW_H
