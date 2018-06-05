
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/bus_rtu/bus_rtusent.h \
    $$PWD/bus_rtu/bus_rturecv.h \
    $$PWD/bus_com/buspacketsi.h \
    $$PWD/bus_rtu/bus_rtucmdenum.h \
    $$PWD/bus_rtu/bus_rtutrans.h \
    $$PWD/bus_dp/bus_dpthread.h \
    $$PWD/bus_dp/bus_dptg.h \
    $$PWD/bus_dp/bus_dpalarm.h \
    $$PWD/bus_mainwid.h \
    $$PWD/bus_simulate/bus_boxtablewid.h \
    $$PWD/bus_simulate/bus_looptablewid.h \
    $$PWD/bus_simulate/bus_bustablewid.h \
    $$PWD/bus_simulate/bus_transtablewid.h \
    $$PWD/bus_simulate/bus_thresholdtablewid.h \
    $$PWD/bus_simulate/bus_envtablewid.h \
    $$PWD/bus_toolbox/bus_toolboxwid.h

	
SOURCES += \
    $$PWD/bus_rtu/bus_rtusent.cpp \
    $$PWD/bus_rtu/bus_rturecv.cpp \
    $$PWD/bus_com/buspacketsi.cpp \
    $$PWD/bus_rtu/bus_rtutrans.cpp \
    $$PWD/bus_dp/bus_dpthread.cpp \
    $$PWD/bus_dp/bus_dptg.cpp \
    $$PWD/bus_dp/bus_dpalarm.cpp \
    $$PWD/bus_mainwid.cpp \
    $$PWD/bus_simulate/bus_boxtablewid.cpp \
    $$PWD/bus_simulate/bus_looptablewid.cpp \
    $$PWD/bus_simulate/bus_bustablewid.cpp \
    $$PWD/bus_simulate/bus_transtablewid.cpp \
    $$PWD/bus_simulate/bus_thresholdtablewid.cpp \
    $$PWD/bus_simulate/bus_envtablewid.cpp \
    $$PWD/bus_toolbox/bus_toolboxwid.cpp

FORMS += \
    $$PWD/bus_mainwid.ui \
    $$PWD/bus_toolbox/bus_toolboxwid.ui





