#ifndef WQ_ANALYSING_WIDGET_H
#define WQ_ANALYSING_WIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QFont>
#include <QScrollArea>
#include <math.h>

namespace Ui {
class WQ_Analysing_Widget;
}

class WQ_Analysing_Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit WQ_Analysing_Widget(QWidget *parent = 0);
    ~WQ_Analysing_Widget();
    void agregarDatos(QString nombreDatos);
    void agregarChart(QString nombreChart);
    void eliminarChart(int numChart);
    void deshabilitarPorDatos(bool estado);
    
private:
    Ui::WQ_Analysing_Widget *ui;

public slots:
    void eliminarDatos(int numDatos);
    void agregarAnalisisManual();
    void agregarSeriesTiempoAutomatico();
    void agregarAnalisisCompletoAutomatico();

signals:
    void graficarUnaAnalisis(int numDatos, int tipoAnalisis, int inicio, int fin, int numChart, bool remplazar);
    void graficarTodasSeriesTiempo(int numDatos, bool remplazar);
;};

#endif // WQ_ANALYSING_WIDGET_H
