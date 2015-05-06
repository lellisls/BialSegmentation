#-------------------------------------------------
#
# Project created by QtCreator 2015-05-05T20:59:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Segmentation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graphicsview.cpp \
    editor.cpp

HEADERS  += mainwindow.h \
    graphicsview.h \
    editor.h

FORMS    += mainwindow.ui
