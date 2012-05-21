#ifndef WQ_WINDOW_H
#define WQ_WINDOW_H

#include <QMainWindow>

namespace Ui {
    class WQ_Window;
}

class WQ_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit WQ_Window(QWidget *parent = 0);
    ~WQ_Window();

private:
    Ui::WQ_Window *ui;
};

#endif // WQ_WINDOW_H
