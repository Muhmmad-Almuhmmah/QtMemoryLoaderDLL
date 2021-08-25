QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

INCLUDEPATH +=source/

SOURCES +=source/MemoryModule.c main.cpp

HEADERS += source/DllLoader.h source/MemoryModule.h

RESOURCES += resource.qrc
