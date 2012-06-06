/********************************************************************************
** Form generated from reading UI file 'wq_window.ui'
**
** Created: Wed Jun 6 15:39:49 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WQ_WINDOW_H
#define UI_WQ_WINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollArea>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WQ_Window
{
public:
    QAction *actionQuit;
    QAction *actionAbout;
    QWidget *centralWidget;
    QWidget *widgetChart1;
    QWidget *widgetChart2;
    QWidget *widgetChart3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPlainTextEdit *plainTextEditConsole;
    QGroupBox *groupBox;
    QRadioButton *radioButtonAnalisis1;
    QRadioButton *radioButtonAnalisis2;
    QRadioButton *radioButtonAnalisis3;
    QWidget *widgetParametros;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WQ_Window)
    {
        if (WQ_Window->objectName().isEmpty())
            WQ_Window->setObjectName(QString::fromUtf8("WQ_Window"));
        WQ_Window->resize(660, 720);
        WQ_Window->setMinimumSize(QSize(660, 720));
        WQ_Window->setMaximumSize(QSize(660, 720));
        WQ_Window->setWindowTitle(QString::fromUtf8("Weight Queue Validator"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("Imagenes/Fractal-Symmetric-Transparent_128x128.png"), QSize(), QIcon::Normal, QIcon::Off);
        WQ_Window->setWindowIcon(icon);
        WQ_Window->setWindowOpacity(1);
        WQ_Window->setStyleSheet(QString::fromUtf8("QGroupBox { \n"
"     border: 2px solid gray; \n"
"     border-radius: 3px; \n"
" } \n"
""));
        WQ_Window->setLocale(QLocale(QLocale::Spanish, QLocale::Colombia));
        WQ_Window->setIconSize(QSize(128, 128));
        WQ_Window->setToolButtonStyle(Qt::ToolButtonIconOnly);
        WQ_Window->setAnimated(true);
        WQ_Window->setDocumentMode(false);
        WQ_Window->setTabShape(QTabWidget::Rounded);
        actionQuit = new QAction(WQ_Window);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionAbout = new QAction(WQ_Window);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralWidget = new QWidget(WQ_Window);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        widgetChart1 = new QWidget(centralWidget);
        widgetChart1->setObjectName(QString::fromUtf8("widgetChart1"));
        widgetChart1->setGeometry(QRect(320, 10, 330, 200));
        widgetChart2 = new QWidget(centralWidget);
        widgetChart2->setObjectName(QString::fromUtf8("widgetChart2"));
        widgetChart2->setGeometry(QRect(320, 230, 330, 200));
        widgetChart3 = new QWidget(centralWidget);
        widgetChart3->setObjectName(QString::fromUtf8("widgetChart3"));
        widgetChart3->setGeometry(QRect(320, 450, 330, 200));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(10, 430, 300, 220));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 298, 218));
        plainTextEditConsole = new QPlainTextEdit(scrollAreaWidgetContents);
        plainTextEditConsole->setObjectName(QString::fromUtf8("plainTextEditConsole"));
        plainTextEditConsole->setGeometry(QRect(0, 0, 300, 220));
        scrollArea->setWidget(scrollAreaWidgetContents);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 300, 130));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setBaseSize(QSize(0, 0));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu"));
        font.setBold(true);
        font.setWeight(75);
        groupBox->setFont(font);
        groupBox->setLayoutDirection(Qt::LeftToRight);
        groupBox->setAutoFillBackground(false);
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        radioButtonAnalisis1 = new QRadioButton(groupBox);
        radioButtonAnalisis1->setObjectName(QString::fromUtf8("radioButtonAnalisis1"));
        radioButtonAnalisis1->setGeometry(QRect(20, 40, 260, 26));
        radioButtonAnalisis2 = new QRadioButton(groupBox);
        radioButtonAnalisis2->setObjectName(QString::fromUtf8("radioButtonAnalisis2"));
        radioButtonAnalisis2->setGeometry(QRect(20, 70, 260, 26));
        radioButtonAnalisis3 = new QRadioButton(groupBox);
        radioButtonAnalisis3->setObjectName(QString::fromUtf8("radioButtonAnalisis3"));
        radioButtonAnalisis3->setGeometry(QRect(20, 100, 260, 26));
        widgetParametros = new QWidget(centralWidget);
        widgetParametros->setObjectName(QString::fromUtf8("widgetParametros"));
        widgetParametros->setGeometry(QRect(10, 150, 300, 260));
        WQ_Window->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WQ_Window);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 660, 29));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        WQ_Window->setMenuBar(menuBar);
        statusBar = new QStatusBar(WQ_Window);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        WQ_Window->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionQuit);
        menuHelp->addAction(actionAbout);

        retranslateUi(WQ_Window);

        QMetaObject::connectSlotsByName(WQ_Window);
    } // setupUi

    void retranslateUi(QMainWindow *WQ_Window)
    {
        actionQuit->setText(QApplication::translate("WQ_Window", "Quit", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("WQ_Window", "About", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("WQ_Window", "Analysing Types", 0, QApplication::UnicodeUTF8));
        radioButtonAnalisis1->setText(QApplication::translate("WQ_Window", "Comparison by time scales", 0, QApplication::UnicodeUTF8));
        radioButtonAnalisis2->setText(QApplication::translate("WQ_Window", "Comparison by probabilistic functions", 0, QApplication::UnicodeUTF8));
        radioButtonAnalisis3->setText(QApplication::translate("WQ_Window", "Tipo de An\303\241lisis 3", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("WQ_Window", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("WQ_Window", "Help", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(WQ_Window);
    } // retranslateUi

};

namespace Ui {
    class WQ_Window: public Ui_WQ_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WQ_WINDOW_H
