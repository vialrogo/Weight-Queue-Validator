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
    wq_iofile.cpp \
    wq_chart.cpp \
    wq_chart_widget.cpp

HEADERS  += \
    wq_window.h \
    wq_validator.h \
    wq_generator.h \
    wq_gen_poisson.h \
    wq_gen_heavytail.h \
    wq_iofile.h \
    wq_chart.h \
    wq_chart_widget.h

FORMS    += \
    wq_chart_widget.ui \
    wq_window.ui

INCLUDEPATH += /usr/include/qwt
LIBS += -l qwt

OTHER_FILES += \
    README
