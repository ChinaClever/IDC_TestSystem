
INCLUDEPATH += $$PWD

include(snmplib/snmplib.pri)

HEADERS += \
    $$PWD/lib/QtSnmpClient.h \
    $$PWD/lib/QtSnmpData.h \
    $$PWD/snmpthread.h \
    $$PWD/snmp_zmrecv.h

	
SOURCES += \
    $$PWD/snmpthread.cpp \
    $$PWD/snmp_zmrecv.cpp

FORMS += \





