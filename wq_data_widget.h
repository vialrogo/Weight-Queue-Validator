#ifndef WQ_DATA_WIDGET_H
#define WQ_DATA_WIDGET_H

#include <QWidget>
#include <QLabel>
#include "wq_button.h"

namespace Ui {
class WQ_Data_Widget;
}

class WQ_Data_Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit WQ_Data_Widget(QWidget *parent = 0);
    ~WQ_Data_Widget();
    void agregarArchivo(QString nombreArchivo);
    
private:
    Ui::WQ_Data_Widget *ui;
    QVector<QLabel*>* vectorNombres;
    QVector<WQ_Button*>* vectorBotonesRemove;

public slots:
    void eliminarArchivoDataWidget(int numFile);

signals:
    void eliminarFileDataWidget(int numFile);
};

#endif // WQ_DATA_WIDGET_H
