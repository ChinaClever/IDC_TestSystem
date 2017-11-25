
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/si_rtu/si_rtu_sent.h \
    $$PWD/si_rtu/si_rtu_recv.h \
    $$PWD/si_rtu/si_rtu_setcmd.h \
    $$PWD/si_rtu/si_rtuthread.h \
    $$PWD/simainwid.h \
    $$PWD/toolbox/sitoolboxwid.h \
    $$PWD/toolbox/sisimulationtoolwid.h \
    $$PWD/toolbox/sitesttoolwid.h \
    $$PWD/toolbox/sisettingtoolwid.h \
    $$PWD/toolbox/sisetlinenum.h \
    $$PWD/toolbox/sisetdevnumdlg.h \
    $$PWD/toolbox/sisetmodbuscmddlg.h \
    $$PWD/si_com/sidatapackets.h \
    $$PWD/si_com/siconfigfile.h \
    $$PWD/si_simulate/si_simulatethread.h

	
SOURCES += \
    $$PWD/si_rtu/si_rtu_sent.cpp \
    $$PWD/si_rtu/si_rtu_recv.cpp \
    $$PWD/si_rtu/si_rtuthread.cpp \
    $$PWD/simainwid.cpp \
    $$PWD/toolbox/sitoolboxwid.cpp \
    $$PWD/toolbox/sisimulationtoolwid.cpp \
    $$PWD/toolbox/sitesttoolwid.cpp \
    $$PWD/toolbox/sisettingtoolwid.cpp \
    $$PWD/toolbox/sisetlinenum.cpp \
    $$PWD/toolbox/sisetdevnumdlg.cpp \
    $$PWD/toolbox/sisetmodbuscmddlg.cpp \
    $$PWD/si_com/sidatapackets.cpp \
    $$PWD/si_com/siconfigfile.cpp \
    $$PWD/si_simulate/si_simulatethread.cpp

FORMS += \
    $$PWD/simainwid.ui \
    $$PWD/toolbox/sitoolboxwid.ui \
    $$PWD/toolbox/sisimulationtoolwid.ui \
    $$PWD/toolbox/sitesttoolwid.ui \
    $$PWD/toolbox/sisettingtoolwid.ui \
    $$PWD/toolbox/sisetlinenum.ui \
    $$PWD/toolbox/sisetdevnumdlg.ui \
    $$PWD/toolbox/sisetmodbuscmddlg.ui





