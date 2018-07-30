
INCLUDEPATH += $$PWD

include(mpdu_test/mpdu_test.pri)

HEADERS += \
    $$PWD/mpdu_mainwid.h \
    $$PWD/mpdu_toolbox/mpdu_toolboxwid.h \
    $$PWD/mpdu_toolbox/mpdu_testtoolwid.h \
    $$PWD/m_rtu/m_rturecv.h \
    $$PWD/m_rtu/m_rtusent.h \
    $$PWD/m_rtu/m_rturegenum.h

	
SOURCES += \
    $$PWD/mpdu_mainwid.cpp \
    $$PWD/mpdu_toolbox/mpdu_toolboxwid.cpp \
    $$PWD/mpdu_toolbox/mpdu_testtoolwid.cpp \
    $$PWD/m_rtu/m_rturecv.cpp \
    $$PWD/m_rtu/m_rtusent.cpp

FORMS += \
    $$PWD/mpdu_mainwid.ui \
    $$PWD/mpdu_toolbox/mpdu_toolboxwid.ui \
    $$PWD/mpdu_toolbox/mpdu_testtoolwid.ui





