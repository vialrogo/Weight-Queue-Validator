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
    WQ_Chart* grafico1;
    WQ_Chart* grafico2;
    WQ_Chart* grafico3;
    QWidget** arregoWidgets;
    int radioButtonSeleccionado;
    WQ_Validator* validador;
    QSize tamanoEstandarGrafico;
    void agregarQuitarBordeChart(int chart, bool bordeBool);

private slots:
    void acercaDe();
    void comparacionEscalasDeTiempo();
    void comparacionFuncionesProbabilidad();
};

#endif // WQ_WINDOW_H
