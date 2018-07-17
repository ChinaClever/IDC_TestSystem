
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/ip_rtu/ip_rtusent.h \
    $$PWD/ip_rtu/ip_rturecv.h \
    $$PWD/ip_com/ipdatapackets.h \
    $$PWD/ip_rtu/ip_rtutrans.h \
    $$PWD/ip_mainwid.h \
    $$PWD/ip_simulate/ip_simulatewid.h \
    $$PWD/ip_simulate/ip_devtablewid.h

	
SOURCES += \
    $$PWD/ip_rtu/ip_rtusent.cpp \
    $$PWD/ip_rtu/ip_rturecv.cpp \
    $$PWD/ip_com/ipdatapackets.cpp \
    $$PWD/ip_rtu/ip_rtutrans.cpp \
    $$PWD/ip_mainwid.cpp \
    $$PWD/ip_simulate/ip_simulatewid.cpp \
    $$PWD/ip_simulate/ip_devtablewid.cpp

FORMS += \
    $$PWD/ip_mainwid.ui \
    $$PWD/ip_simulate/ip_simulatewid.ui





