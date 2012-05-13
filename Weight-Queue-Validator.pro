#-------------------------------------------------
#
# Project created by QtCreator 2011-09-14T09:54:30
#
#-------------------------------------------------

QT       += core gui

TARGET = Weight-Queue-Validator
TEMPLATE = app


SOURCES += main.cpp\
        wq_validator.cpp

HEADERS  += wq_validator.h

FORMS    += wq_validator.ui

INCLUDEPATH += /usr/include/qwt
LIBS += -l qwt

OTHER_FILES += \
    README
