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
    void configurarInterfaz(bool cual);

    //Objetos time view
    QComboBox* comboDatos;
    QLabel* labelDuration;
    QLabel* labelStart;
    QSpinBox* spinDurationSegundos;
    QSpinBox* spinStartSegundos;
    QSpinBox* spinDurationMilis;
    QSpinBox* spinStartMilis;
    QSpinBox* spinDurationMicros;
    QSpinBox* spinStartMicros;
    QLabel* labelDurationSegundos;
    QLabel* labelStartSegundos;
    QLabel* labelDurationMilis;
    QLabel* labelStartMilis;
    QLabel* labelDurationMicros;
    QLabel* labelStartMicros;
    QComboBox* comboChart;
    QCheckBox* checkBoxReplace;
    QFont* fuenteBotones;
    QPushButton* botonAutomatic;
    QPushButton* botonAddCurve;

    //Objetos data analysing

    //Objetos comunes
    QScrollArea* scrollArea;
    QWidget* widgetDatos;

public slots:
    void configurarWidgetTiempo();
    void configurarWidgetDatos();
    void eliminarDatos(int numDatos);
    void agregarSerieTiempoManual();

signals:
    void graficarUnaSerieTiempo(int numDatos, int inicio, int fin, int numChart, bool remplazar);
;};

#endif // WQ_ANALYSING_WIDGET_H
