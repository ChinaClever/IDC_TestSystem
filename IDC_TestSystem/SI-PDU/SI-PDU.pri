
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/si_modbus/si_modbusread.h \
    $$PWD/si_modbus/si_rtu/si_rtu_sent.h \
    $$PWD/si_modbus/si_rtu/si_rtu_recv.h \
    $$PWD/si_modbus/si_rtu/si_rtu_setcmd.h \
    $$PWD/si_modbus/si_rtu/si_rtuthread.h

	
SOURCES += \
    $$PWD/si_modbus/si_modbusread.cpp \
    $$PWD/si_modbus/si_rtu/si_rtu_sent.cpp \
    $$PWD/si_modbus/si_rtu/si_rtu_recv.cpp \
    $$PWD/si_modbus/si_rtu/si_rtuthread.cpp





