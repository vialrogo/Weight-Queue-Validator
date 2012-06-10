#ifndef WQ_CHART_WIDGET_H
#define WQ_CHART_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class WQ_Chart_Widget;
}

class WQ_Chart_Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit WQ_Chart_Widget(QWidget *parent = 0);
    ~WQ_Chart_Widget();
    int agregarCurva(QString nombreCurva);
    
private:
    Ui::WQ_Chart_Widget *ui;
    QVector<QLabel*>* vectorNombres;
    QVector<QPushButton*>* vectorBotonesView;
    QVector<QPushButton*>* vectorBotonesRemove;
};

#endif // WQ_CHART_WIDGET_H
