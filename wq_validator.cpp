#include "wq_validator.h"
#include "ui_wq_validator.h"

WQ_Validator::WQ_Validator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WQ_Validator)
{
    ui->setupUi(this);
}

WQ_Validator::~WQ_Validator()
{
    delete ui;
}

//Aquí estuve :P
//Otra vez
