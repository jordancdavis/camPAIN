#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T20:09:06
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = camPAIN
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    signupdialog.cpp \
    gamemainmenuwindow.cpp \
    continuedgamemenuwindow.cpp \
    startnewgamewindow.cpp \
    characterbiowindow.cpp \
    campainleaderboardwindow.cpp \
    compatabilityquizwindow.cpp \
    selectcharacterwindow.cpp \
    debatewindow.cpp \
    biodialog.cpp \
    game.cpp \
    question.cpp \
    client.cpp \
    dbserver.cpp \
    logindialog.cpp \
    mycanvas.cpp \
    qsfmlcanvas.cpp \
    myserver.cpp \
    mythread.cpp \
    webserver.cpp \
    webthread.cpp \
    worldsettingswindow.cpp \
    youwindialog.cpp

HEADERS  += mainwindow.h \
    signupdialog.h \
    gamemainmenuwindow.h \
    continuedgamemenuwindow.h \
    startnewgamewindow.h \
    characterbiowindow.h \
    campainleaderboardwindow.h \
    compatabilityquizwindow.h \
    selectcharacterwindow.h \
    debatewindow.h \
    biodialog.h \
    question.h \
    game.h \
    client.h \
    dbserver.h \
    logindialog.h \
    mycanvas.h \
    qsfmlcanvas.h \
    myserver.h \
    mythread.h \
    webserver.h \
    webthread.h \
    worldsettingswindow.h \
    youwindialog.h

FORMS    += mainwindow.ui \
    signupdialog.ui \
    gamemainmenuwindow.ui \
    continuedgamemenuwindow.ui \
    startnewgamewindow.ui \
    characterbiowindow.ui \
    campainleaderboardwindow.ui \
    compatabilityquizwindow.ui \
    selectcharacterwindow.ui \
    debatewindow.ui \
    biodialog.ui \
    logindialog.ui \
    worldsettingswindow.ui \
    youwindialog.ui


macx: LIBS += -L/usr/local/Cellar/sfml/2.3_1/lib/ -lsfml-audio.2.3.0
INCLUDEPATH += /usr/local/Cellar/sfml/2.3_1/include
DEPENDPATH += /usr/local/Cellar/sfml/2.3_1/include

macx: LIBS += -L/usr/local/Cellar/sfml/2.3_1/lib/ -lsfml-graphics.2.3.0
INCLUDEPATH += /usr/local/Cellar/sfml/2.3_1/include
DEPENDPATH += /usr/local/Cellar/sfml/2.3_1/include

macx: LIBS += -L/usr/local/Cellar/sfml/2.3_1/lib/ -lsfml-network.2.3.0
INCLUDEPATH += /usr/local/Cellar/sfml/2.3_1/include
DEPENDPATH += /usr/local/Cellar/sfml/2.3_1/include

macx: LIBS += -L/usr/local/Cellar/sfml/2.3_1/lib/ -lsfml-window.2.3.0
INCLUDEPATH += /usr/local/Cellar/sfml/2.3_1/include
DEPENDPATH += /usr/local/Cellar/sfml/2.3_1/include

macx: LIBS += -L/usr/local/Cellar/sfml/2.3_1/lib/ -lsfml-system.2.3.0
INCLUDEPATH += /usr/local/Cellar/sfml/2.3_1/include
DEPENDPATH += /usr/local/Cellar/sfml/2.3_1/include


RESOURCES += \
    resources.qrc

##MYSQL
macx: LIBS += -L$$PWD/mysql-5.7.12-osx10.11-x86_64/lib/ -lmysqlclient

INCLUDEPATH += $$PWD/mysql-5.7.12-osx10.11-x86_64/include
DEPENDPATH += $$PWD/mysql-5.7.12-osx10.11-x86_64/include

macx: PRE_TARGETDEPS += $$PWD/mysql-5.7.12-osx10.11-x86_64/lib/libmysqlclient.a


##BOX 2D
macx: LIBS += -L$$PWD/Box2D/lib/ -lBox2D.2.3.0

INCLUDEPATH += $$PWD/Box2D/include
DEPENDPATH += $$PWD/Box2D/include

CONFIG += warn_off
