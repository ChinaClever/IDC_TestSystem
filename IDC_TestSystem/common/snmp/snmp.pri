
INCLUDEPATH += $$PWD

include(snmplib/snmplib.pri)

HEADERS += \
    $$PWD/snmpthread.h \
    $$PWD/snmp_zmrecv.h

	
SOURCES += \
    $$PWD/snmpthread.cpp \
    $$PWD/snmp_zmrecv.cpp

FORMS += \





