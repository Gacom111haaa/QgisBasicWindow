#-------------------------------------------------
#
# Project created by QtCreator 2017-03-01T23:13:09
#
#-------------------------------------------------

QT       += core gui
QT += widgets
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BasicWindow
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS += -L/usr/local/lib/ -lqgis_core -lqgis_gui
INCLUDEPATH += /usr/include/qgis
DEFINES += GUI_EXPORT= CORE_EXPORT=
