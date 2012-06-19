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

namespace Ui {
class WQ_Analysing_Widget;
}

class WQ_Analysing_Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit WQ_Analysing_Widget(QWidget *parent = 0);
    ~WQ_Analysing_Widget();
    
private:
    Ui::WQ_Analysing_Widget *ui;
    void configurarInterfaz(bool cual);

    //Objetos time view
    QComboBox* comboDatos;
    QLabel* labelDuration;
    QLabel* labelStart;
    QSpinBox* spinDuration;
    QSpinBox* spinStart;
    QComboBox* comboDuration;
    QComboBox* comboStart;
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

signals:

;};

#endif // WQ_ANALYSING_WIDGET_H
