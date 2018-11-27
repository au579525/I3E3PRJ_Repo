TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
TARGET = index.cgi

SOURCES += main.cpp \
    htmlpage.cpp \
    fileaccess.cpp \
    postrequest.cpp

unix:!macx: LIBS += -L$$PWD/../../../../../opt/rpicgi/lib -lcgicc

INCLUDEPATH += $$PWD/../../../../../opt/rpicgi/include
DEPENDPATH += $$PWD/../../../../../opt/rpicgi/include

HEADERS += \
    htmlpage.h \
    fileaccess.h \
    postrequest.h
