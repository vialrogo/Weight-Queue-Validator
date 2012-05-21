#include <QtGui/QApplication>
#include "wq_window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WQ_Window w;
    w.show();

    return a.exec();
}
