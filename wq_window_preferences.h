#ifndef WQ_WINDOW_PREFERENCES_H
#define WQ_WINDOW_PREFERENCES_H

#include <QDialog>

namespace Ui {
class WQ_Window_Preferences;
}

class WQ_Window_Preferences : public QDialog
{
    Q_OBJECT
    
public:
    explicit WQ_Window_Preferences(QWidget *parent = 0);
    ~WQ_Window_Preferences();
    
private:
    Ui::WQ_Window_Preferences *ui;
};

#endif // WQ_WINDOW_PREFERENCES_H
