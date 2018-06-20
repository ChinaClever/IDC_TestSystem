
INCLUDEPATH += $$PWD

include(mpdu_test/mpdu_test.pri)

HEADERS += \
    $$PWD/mpdu_mainwid.h \
    $$PWD/mpdu_toolbox/mpdu_toolboxwid.h

	
SOURCES += \
    $$PWD/mpdu_mainwid.cpp \
    $$PWD/mpdu_toolbox/mpdu_toolboxwid.cpp

FORMS += \
    $$PWD/mpdu_mainwid.ui \
    $$PWD/mpdu_toolbox/mpdu_toolboxwid.ui





