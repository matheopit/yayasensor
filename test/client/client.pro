TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    ../core/mgclientbase.cpp \
    ../core/mgutils.cpp \
    ../core/mgremotebuffer.cpp \
    ../core/mgclient.cpp



INCLUDEPATH += $$PWD/../../lib/include \
               $$PWD/../core
LIBS += -L$$PWD/../../lib/lib -luv


HEADERS += \
    ../core/mgclientbase.h \
    ../core/mgutils.h \
    ../core/mgclient.h \
    ../core/mgbufferclient.h \
    ../core/mgremotebuffer.h

