#include "wq_button.h"

WQ_Button::WQ_Button(const QIcon & icon, const QString & text, QWidget * parent, int numItem_in) :
    QPushButton(icon, text, parent)
{
    numeroItem = numItem_in;

    connect(this,SIGNAL(clicked()),this, SLOT(fuePulsado()));
}

void WQ_Button::setNumeroItem(int numItem_in)
{
    numeroItem=numItem_in;
}

int WQ_Button::getNumeroItem()
{
    return numeroItem;
}

void WQ_Button::fuePulsado()
{
    emit pulsado(numeroItem);
}

