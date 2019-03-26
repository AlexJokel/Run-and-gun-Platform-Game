#-------------------------------------------------
#
# Project created by QtCreator 2019-02-26T10:33:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Run-and-gun-Platform-Game
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src

SOURCES += \
    src/main.cpp \
    src/player.cpp \
    src/object.cpp \
    src/creature.cpp \
    src/ground.cpp \
    src/arrow.cpp \
    src/contactlistener.cpp \
    src/level.cpp \
    src/scene.cpp

HEADERS += \
#    Box2D/Box2D.h
    src/player.h \
    src/object.h \
    src/creature.h \
    src/ground.h \
    src/arrow.h \
    src/contactlistener.h \
    src/level.h \
    src/scene.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/lib/ -lBox2D

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/Box2D.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/libBox2D.a
