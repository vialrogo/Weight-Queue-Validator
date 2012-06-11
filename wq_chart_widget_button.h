#ifndef WQ_CHART_WIDGET_BUTTON_H
#define WQ_CHART_WIDGET_BUTTON_H

#include <QPushButton>

class WQ_Chart_Widget_Button : public QPushButton
{
    Q_OBJECT

public:
    WQ_Chart_Widget_Button(const QIcon & icon, const QString & text, QWidget * parent = 0, int numCurva_in=0);
    int getNumeroCurva();
    void setNumeroCurva(int numCurva_in);

private:
    int numeroCurva;

public slots:
    void fuePulsado();

signals:
    void pulsado(int numeroCurva_in);
};

#endif // WQ_CHART_WIDGET_BUTTON_H
