#ifndef WQ_BUTTON_H
#define WQ_BUTTON_H

#include <QPushButton>

class WQ_Button : public QPushButton
{
    Q_OBJECT

public:
    WQ_Button(const QIcon & icon, const QString & text, QWidget * parent = 0, int numItem_in=0);
    int getNumeroItem();
    void setNumeroItem(int numItem_in);

private:
    int numeroItem;

public slots:
    void fuePulsado();

signals:
    void pulsado(int numeroItem_in);
};

#endif // WQ_BUTTON_H
