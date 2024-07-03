#-------------------------------------------------
#
# Project created by QtCreator 2020-09-30T23:17:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BlueStacks
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

SOURCES += \
        main.cpp \
        slideshow.cpp \
    mainwidget.cpp \
    customtoolbutton.cpp \
    customlabel.cpp \
    customwidget.cpp \
    custommenu.cpp \
    customframe.cpp

HEADERS += \
        slideshow.h \
    mainwidget.h \
    customtoolbutton.h \
    customlabel.h \
    customwidget.h \
    custommenu.h \
    customframe.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sliderresource.qrc

DISTFILES += \
    XML/countries.xml \
    images/game-war-bg.jpg \
    images/king-avalon_banner.jpg \
    images/lords-mobile_banner.jpg \
    Countries/br.png \
    Countries/cn.png \
    Countries/cz.png \
    Countries/de.png \
    Countries/es.png \
    Countries/fr.png \
    Countries/id.png \
    Countries/it.png \
    Countries/jp.png \
    Countries/kr.png \
    Countries/my.png \
    Countries/nl.png \
    Countries/ru.png \
    Countries/sa.png \
    Countries/th.png \
    Countries/tw.png \
    Countries/us.png \
    Countries/vn.png \
    resources/officialLogo.png \
    resources/white-arrow-down.png \
    resources/favicon.ico
