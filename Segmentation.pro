#-------------------------------------------------
#
# Project created by QtCreator 2015-05-05T20:59:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Segmentation
TEMPLATE = app


SOURCES += \
    ../bial/src/StaticMembers.cpp \
    ../bial/src/StaticBial.cpp \
    ../bial/src/Dicomdir.cpp \
    ../bial/src/Patient.cpp \
    ../bial/src/Series.cpp \
    ../bial/src/Study.cpp \
    ../bial/src/ImageInfo.cpp \
    ../bial/lsh/BucketHashing.cpp \
    ../bial/lsh/Geometry.cpp \
    ../bial/lsh/GlobalVars.cpp \
    ../bial/lsh/LocalitySensitiveHashing.cpp \
    ../bial/lsh/LSH.cpp \
    ../bial/lsh/NearNeighbors.cpp \
    ../bial/lsh/Random.cpp \
    ../bial/lsh/SelfTuning.cpp \
    ../bial/gui/src/segmentationeditor.cpp \
    ../bial/gui/src/segmentationarea.cpp \
    ../bial/gui/src/graphicsview.cpp \
    main.cpp \
    mainwindow.cpp \
    cursorchanger.cpp \
    imagecontroller.cpp \
    ../bial/gui/src/guiimage.cpp

HEADERS  += \
    ../bial/gui/inc/segmentationeditor.h \
    ../bial/gui/inc/segmentationarea.h \
    ../bial/gui/inc/graphicsview.hpp \
    ../bial/gui/inc/guiimage.hpp \
    mainwindow.h \
    bialqt.hpp \
    cursorchanger.h \
    imagecontroller.h

FORMS    += mainwindow.ui

INCLUDEPATH += inc ../bial/inc ../bial/lsh ../bial/gui/inc
LIBS += -lz -fopenmp

QMAKE_CXXFLAGS_RELEASE  = -Ofast
QMAKE_CXXFLAGS_DEBUG += -O0 -DBIAL_DEBUG=1
QMAKE_CXXFLAGS += -std=c++11 -DREAL_FLOAT
QMAKE_LFLAGS += -O3
