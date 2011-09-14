#ifndef WQ_VALIDATOR_H
#define WQ_VALIDATOR_H

#include <QMainWindow>

namespace Ui {
    class WQ_Validator;
}

class WQ_Validator : public QMainWindow
{
    Q_OBJECT

public:
    explicit WQ_Validator(QWidget *parent = 0);
    ~WQ_Validator();

private:
    Ui::WQ_Validator *ui;
};

#endif // WQ_VALIDATOR_H
