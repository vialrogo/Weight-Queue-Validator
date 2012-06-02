#ifndef WQ_CHART_H
#define WQ_CHART_H

#include <qwt_plot.h>

class WQ_Chart: public QwtPlot
{
private:

public:
    WQ_Chart(QWidget* parent = 0);
};

#endif // WQ_CHART_H
