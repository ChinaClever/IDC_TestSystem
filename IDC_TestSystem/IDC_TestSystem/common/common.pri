
INCLUDEPATH += $$PWD

include(snmp/snmp.pri)
include(chars/chars.pri)
include(excel/excel.pri)
include(dpcom/dpcom.pri)
include(rtucom/rtucom.pri)
include(logcom/logcom.pri)
include(sqlcom/sqlcom.pri)
include(testcom/testcom.pri)
include(tablewid/tablewid.pri)
include(toolbox/toolbox.pri)
include(websocket/websocket.pri)
include(serialport/serialport.pri)

HEADERS += \	
    $$PWD/common.h \
    $$PWD/msgbox.h \
    $$PWD/sysconfigfile.h \
    $$PWD/configbase.h \
#    common/qcustomplot.h \
    $$PWD/datapacket.h \
	
SOURCES += \	
    $$PWD/common.cpp \
    $$PWD/msgbox.cpp \
    $$PWD/sysconfigfile.cpp \
    $$PWD/configbase.cpp \
#    common/qcustomplot.cpp \

FORMS += \




