#-------------------------------------------------
#
# Project created by QtCreator 2018-07-03T14:09:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = modelviewTest
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    studentmodel.cpp \
    studentdelegate.cpp

HEADERS  += widget.h \
    studentmodel.h \
    studentdelegate.h

FORMS    += widget.ui

RESOURCES += \
    image.qrc
