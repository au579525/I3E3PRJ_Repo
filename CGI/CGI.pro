TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
TARGET = index.cgi

SOURCES += main.cpp \
    htmlpage.cpp \
    fileaccess.cpp \
    postrequest.cpp

unix:!macx: LIBS += -L$$PWD/../../../../../opt/lib/ -lcgicc

INCLUDEPATH += $$PWD/../../../../../opt/include
DEPENDPATH += $$PWD/../../../../../opt/include

HEADERS += \
    htmlpage.h \
    fileaccess.h \
    postrequest.h
