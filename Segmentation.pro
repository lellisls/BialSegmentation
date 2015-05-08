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
    main.cpp \
    mainwindow.cpp \
    graphicsview.cpp \
    segmentationarea.cpp \
    editor.cpp \
    cursorchanger.cpp

HEADERS  += \
    mainwindow.h \
    graphicsview.h \
    bialqt.hpp \
    ../bial/gui/inc/guiimage.hpp \
    segmentationarea.h \
    editor.h \
    cursorchanger.h

FORMS    += mainwindow.ui

INCLUDEPATH += inc ../bial/inc ../bial/lsh
LIBS += -lz

QMAKE_CXXFLAGS_RELEASE  = -Ofast
QMAKE_CXXFLAGS_DEBUG += -O0 -DBIAL_DEBUG=1
QMAKE_CXXFLAGS += -std=c++11 -DREAL_FLOAT
QMAKE_LFLAGS += -O3
