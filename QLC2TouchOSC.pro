QT += core
QT -= gui
QT += xml

TARGET = QLC2TouchOSC
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    totouchosc.cpp

HEADERS += \
    totouchosc.h


