#include "wq_chart_widget_button.h"

WQ_Chart_Widget_Button::WQ_Chart_Widget_Button(const QIcon & icon, const QString & text, QWidget * parent, int numCurva_in) :
    QPushButton(icon, text, parent)
{
    numeroCurva = numCurva_in;

    connect(this,SIGNAL(clicked()),this, SLOT(fuePulsado()));
}

void WQ_Chart_Widget_Button::setNumeroCurva(int numCurva_in)
{
    numeroCurva=numCurva_in;
}

int WQ_Chart_Widget_Button::getNumeroCurva()
{
    return numeroCurva;
}

void WQ_Chart_Widget_Button::fuePulsado()
{
    emit pulsado(numeroCurva);
}

