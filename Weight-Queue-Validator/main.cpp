#include <QtGui/QApplication>
#include "wq_validator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WQ_Validator w;
    w.show();

    return a.exec();
}
