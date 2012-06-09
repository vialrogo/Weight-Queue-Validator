#ifndef WQ_WINDOW_H
#define WQ_WINDOW_H

#include <QMessageBox>
#include <QMainWindow>
#include "ui_wq_window.h"
#include "wq_chart.h"
#include "wq_validator.h"

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
    QSize tamanoEstandarGrafico;
    WQ_Validator* validador;
    QWidget** arregoWidgets;
    QVector<WQ_Chart*> vectorCharts;

    void agregarQuitarBordeChart(int chart, bool bordeBool);
    void agregarChart();

private slots:
    void acercaDe();
    void comparacionEscalasDeTiempo();
    void comparacionFuncionesProbabilidad();
};

#endif // WQ_WINDOW_H
