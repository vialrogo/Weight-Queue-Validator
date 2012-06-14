#include "wq_window_preferences.h"
#include "ui_wq_window_preferences.h"

WQ_Window_Preferences::WQ_Window_Preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WQ_Window_Preferences)
{
    ui->setupUi(this);
}

WQ_Window_Preferences::~WQ_Window_Preferences()
{
    delete ui;
}
