#-------------------------------------------------
#
# Project created by QtCreator 2017-11-06T13:53:34
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network
QT       += serialport
QT       += printsupport
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IDC_TestSystem
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

include(common/common.pri)
include(serialport/serialport.pri)
include(SI-PDU/SI-PDU.pri)
include(IP-PDU/IP-PDU.pri)
include(sql/sql.pri)
include(logs/logs.pri)
include(excel/excel.pri)
include(eload/eload.pri)
include(test/test.pri)

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    images/image.qrc
