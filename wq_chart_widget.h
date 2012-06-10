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
    explicit WQ_Chart_Widget(QWidget *parent = 0, int numChart_in=0);
    ~WQ_Chart_Widget();
    int agregarCurva(QString nombreCurva);
    int getNumChart();
    void setNumChart(int numeroChart_in);
    
private:
    Ui::WQ_Chart_Widget *ui;
    int numeroChart;
    QVector<QLabel*>* vectorNombres;
    QVector<QPushButton*>* vectorBotonesView;
    QVector<QPushButton*>* vectorBotonesRemove;

private slots:
    void clickBotonEliminarChart();

signals:
    int eliminarChart(int numeroChart);
};

#endif // WQ_CHART_WIDGET_H
