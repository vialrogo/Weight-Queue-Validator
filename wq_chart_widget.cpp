#include "wq_chart_widget.h"
#include "ui_wq_chart_widget.h"

WQ_Chart_Widget::WQ_Chart_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WQ_Chart_Widget)
{
    ui->setupUi(this);
}

WQ_Chart_Widget::~WQ_Chart_Widget()
{
    delete ui;
}
