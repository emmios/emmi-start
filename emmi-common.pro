QT += core
QT -= gui


TARGET = emmi-common
CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    threads.cpp

HEADERS += \
    threads.h

INCLUDEPATH += /home/shenoisz/Qt5.5.1/5.5/gcc_64/include
