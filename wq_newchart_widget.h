#ifndef WQ_NEWCHART_WIDGET_H
#define WQ_NEWCHART_WIDGET_H

#include <QWidget>

namespace Ui {
class WQ_NewChart_Widget;
}

class WQ_NewChart_Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit WQ_NewChart_Widget(QWidget *parent = 0);
    ~WQ_NewChart_Widget();
    void configurarWidgetAnalisis();
    void configurarWidgetSimulacion();
    
private:
    Ui::WQ_NewChart_Widget *ui;
};

#endif // WQ_NEWCHART_WIDGET_H
