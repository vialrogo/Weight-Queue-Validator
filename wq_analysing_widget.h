#ifndef WQ_ANALYSING_WIDGET_H
#define WQ_ANALYSING_WIDGET_H

#include <QWidget>

namespace Ui {
class WQ_Analysing_Widget;
}

class WQ_Analysing_Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit WQ_Analysing_Widget(QWidget *parent = 0);
    ~WQ_Analysing_Widget();
    void configurarWidgetAnalisis();
    void configurarWidgetSimulacion();
    
private:
    Ui::WQ_Analysing_Widget *ui;

public slots:
    void escogioAnalisis();
    void escogioSimulacion();

signals:
    void analizar();
    void simular()
;};

#endif // WQ_ANALYSING_WIDGET_H
