#ifndef WQ_WINDOW_H
#define WQ_WINDOW_H

#include <QMessageBox>
#include <QMainWindow>
#include <iostream>
#include "ui_wq_window.h"
#include "wq_chart.h"
#include "wq_validator.h"

using namespace std;

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
    QVector<WQ_Chart*> vectorCharts;
    QVector<QVector <QVector<QPointF>* >* >* vectorCurvasPorChart;

    void agregarQuitarBordeWidgets(int numWidget, bool bordeBool);
    int agregarChart();
    void eliminarChart(int numChart);
    void colocarWidgetEnPosicion(int numWidget, int posicion);
    void agregarCurvaAChart(int numChart, QString nombreCurva, QVector<QPointF>* datos);

private slots:
    void acercaDe();
    void comparacionEscalasDeTiempo();
    void comparacionFuncionesProbabilidad();
    void comparacion3NombreTemporal();
};

#endif // WQ_WINDOW_H
