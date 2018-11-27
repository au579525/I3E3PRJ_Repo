TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
TARGET = index.cgi

SOURCES += main.cpp \
    htmlpage.cpp \
    fileaccess.cpp \
    postrequest.cpp

HEADERS += \
    htmlpage.h \
    fileaccess.h \
    postrequest.h

unix:!macx: LIBS += -L$$PWD/lib/ -lcgicc

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
