#include "wq_data_widget.h"
#include "ui_wq_data_widget.h"

WQ_Data_Widget::WQ_Data_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WQ_Data_Widget)
{
    ui->setupUi(this);
}

WQ_Data_Widget::~WQ_Data_Widget()
{
    delete ui;
}
