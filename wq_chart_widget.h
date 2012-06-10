#ifndef WQ_CHART_WIDGET_H
#define WQ_CHART_WIDGET_H

#include <QWidget>

namespace Ui {
class WQ_Chart_Widget;
}

class WQ_Chart_Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit WQ_Chart_Widget(QWidget *parent = 0);
    ~WQ_Chart_Widget();
    
private:
    Ui::WQ_Chart_Widget *ui;
};

#endif // WQ_CHART_WIDGET_H
