#ifndef WQ_DATA_WIDGET_H
#define WQ_DATA_WIDGET_H

#include <QWidget>

namespace Ui {
class WQ_Data_Widget;
}

class WQ_Data_Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit WQ_Data_Widget(QWidget *parent = 0);
    ~WQ_Data_Widget();
    
private:
    Ui::WQ_Data_Widget *ui;
};

#endif // WQ_DATA_WIDGET_H
