#include "wq_window.h"
#include "ui_wq_window.h"

WQ_Window::WQ_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WQ_Window)
{
    ui->setupUi(this);
}

WQ_Window::~WQ_Window()
{
    delete ui;
}
