# Auto-generated by IDE. All changes by user will be lost!
# Created at 09/02/13 11:49 AM

BASEDIR = $$_PRO_FILE_PWD_

INCLUDEPATH +=  \
    $$BASEDIR/src/EMULib/QNX \
    $$BASEDIR/src/ATI85/QNX \
    $$BASEDIR/src/Z80 \
    $$BASEDIR/src/Browser \
    $$BASEDIR/src/EMULib \
    $$BASEDIR/src/ATI85 \
    $$BASEDIR/src

SOURCES +=  \
    $$BASEDIR/src/ATI85/ATI85.cpp \
    $$BASEDIR/src/ATI85/QNX/QNX.cpp \
    $$BASEDIR/src/ATI85/QNX/lodepng.cpp \
    $$BASEDIR/src/ATI85/TI85.cpp \
    $$BASEDIR/src/ActiveFrame.cpp \
    $$BASEDIR/src/AlmostTIPb.cpp \
    $$BASEDIR/src/Browser/FolderBrowser.cpp \
    $$BASEDIR/src/EMULib/Console.cpp \
    $$BASEDIR/src/EMULib/EMULib.cpp \
    $$BASEDIR/src/EMULib/INIFile.cpp \
    $$BASEDIR/src/EMULib/Image.cpp \
    $$BASEDIR/src/EMULib/NetPlay.cpp \
    $$BASEDIR/src/EMULib/QNX/LibQNX.cpp \
    $$BASEDIR/src/EMULib/QNX/NetQNX.cpp \
    $$BASEDIR/src/EMULib/QNX/SndQNX.cpp \
    $$BASEDIR/src/EMULib/Sound.cpp \
    $$BASEDIR/src/EMULib/Touch.cpp \
    $$BASEDIR/src/Z80/ConDebug.cpp \
    $$BASEDIR/src/Z80/Z80.cpp \
    $$BASEDIR/src/main.cpp

HEADERS +=  \
    $$BASEDIR/src/ATI85/Common.h \
    $$BASEDIR/src/ATI85/Help.h \
    $$BASEDIR/src/ATI85/TI85.h \
    $$BASEDIR/src/ActiveFrame.hpp \
    $$BASEDIR/src/AlmostTIPb.hpp \
    $$BASEDIR/src/Browser/FolderBrowser.hpp \
    $$BASEDIR/src/EMULib/Console.h \
    $$BASEDIR/src/EMULib/ConsoleMux.h \
    $$BASEDIR/src/EMULib/EMULib.h \
    $$BASEDIR/src/EMULib/INIFile.h \
    $$BASEDIR/src/EMULib/ImageMux.h \
    $$BASEDIR/src/EMULib/LibARM.h \
    $$BASEDIR/src/EMULib/MIDIFreq.h \
    $$BASEDIR/src/EMULib/NetPlay.h \
    $$BASEDIR/src/EMULib/QNX/LibQNX.h \
    $$BASEDIR/src/EMULib/Sound.h \
    $$BASEDIR/src/EMULib/Touch.h \
    $$BASEDIR/src/EMULib/TouchMux.h \
    $$BASEDIR/src/Z80/Codes.h \
    $$BASEDIR/src/Z80/CodesCB.h \
    $$BASEDIR/src/Z80/CodesED.h \
    $$BASEDIR/src/Z80/CodesXCB.h \
    $$BASEDIR/src/Z80/CodesXX.h \
    $$BASEDIR/src/Z80/Debug.h \
    $$BASEDIR/src/Z80/Tables.h \
    $$BASEDIR/src/Z80/Z80.h \
    $$BASEDIR/src/config.h

lupdate_inclusion {
    SOURCES += \
        $$BASEDIR/../assets/*.qml
}

TRANSLATIONS = \
    $${TARGET}.ts
