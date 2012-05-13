/********************************************************************************
** Form generated from reading UI file 'wq_validator.ui'
**
** Created: Sun May 13 13:26:02 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WQ_VALIDATOR_H
#define UI_WQ_VALIDATOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WQ_Validator
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WQ_Validator)
    {
        if (WQ_Validator->objectName().isEmpty())
            WQ_Validator->setObjectName(QString::fromUtf8("WQ_Validator"));
        WQ_Validator->resize(400, 300);
        menuBar = new QMenuBar(WQ_Validator);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        WQ_Validator->setMenuBar(menuBar);
        mainToolBar = new QToolBar(WQ_Validator);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        WQ_Validator->addToolBar(mainToolBar);
        centralWidget = new QWidget(WQ_Validator);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        WQ_Validator->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(WQ_Validator);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        WQ_Validator->setStatusBar(statusBar);

        retranslateUi(WQ_Validator);

        QMetaObject::connectSlotsByName(WQ_Validator);
    } // setupUi

    void retranslateUi(QMainWindow *WQ_Validator)
    {
        WQ_Validator->setWindowTitle(QApplication::translate("WQ_Validator", "WQ_Validator", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WQ_Validator: public Ui_WQ_Validator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WQ_VALIDATOR_H
