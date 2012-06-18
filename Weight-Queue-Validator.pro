#-------------------------------------------------
#
# Project created by QtCreator 2011-09-14T09:54:30
#
#-------------------------------------------------

QT       += core gui

TARGET = Weight-Queue-Validator
TEMPLATE = app


SOURCES += main.cpp \
    wq_window.cpp \
    wq_validator.cpp \
    wq_generator.cpp \
    wq_gen_poisson.cpp \
    wq_gen_heavytail.cpp \
    wq_chart.cpp \
    wq_chart_widget.cpp \
    wq_data_widget.cpp \
    wq_button.cpp \
    wq_iofiles.cpp \
    wq_window_preferences.cpp \
    wq_newchart_widget.cpp

HEADERS  += \
    wq_window.h \
    wq_validator.h \
    wq_generator.h \
    wq_gen_poisson.h \
    wq_gen_heavytail.h \
    wq_chart.h \
    wq_chart_widget.h \
    wq_data_widget.h \
    wq_button.h \
    wq_iofiles.h \
    wq_window_preferences.h \
    wq_newchart_widget.h

FORMS    += \
    wq_chart_widget.ui \
    wq_window.ui \
    wq_data_widget.ui \
    wq_window_preferences.ui \
    wq_newchart_widget.ui

INCLUDEPATH += /usr/include/qwt
LIBS += -l qwt

OTHER_FILES += \
    README
