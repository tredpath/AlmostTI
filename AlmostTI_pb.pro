TEMPLATE = app
TARGET = AlmostTI_pb

CONFIG += qt warn_on debug_and_release cascades

INCLUDEPATH += ../src
SOURCES += ../src/*.cpp ../src/ATI85/*.cpp ../src/EMULib/*.cpp ../src/Z80/*.cpp ../src/EMULib/QNX/*.cpp ../src/ATI85/QNX/*.cpp ../src/Browser/*.cpp
HEADERS += ../src/*.hpp ../src/*.h ../src/ATI85/*.h ../src/EMULib/*.h ../src/Z80/*.h ../src/EMULib/QNX/*.h ../src/ATI85/QNX/*.h ../src/Browser/*.hpp
LIBS += -lbbsystem -lscreen -lsocket -lpng -lbb -lbbdevice

lupdate_inclusion {
    SOURCES += ../assets/*.qml
}

device {
	CONFIG(release, debug|release) {
		DESTDIR = o.le-v7
	}
	CONFIG(debug, debug|release) {
		DESTDIR = o.le-v7-g
	}
}

simulator {
	CONFIG(release, debug|release) {
		DESTDIR = o
	}
	CONFIG(debug, debug|release) {
		DESTDIR = o-g
	}
}

OBJECTS_DIR = $${DESTDIR}/.obj
MOC_DIR = $${DESTDIR}/.moc
RCC_DIR = $${DESTDIR}/.rcc
UI_DIR = $${DESTDIR}/.ui

suredelete.target = sureclean
suredelete.commands = $(DEL_FILE) $${MOC_DIR}/*; $(DEL_FILE) $${RCC_DIR}/*; $(DEL_FILE) $${UI_DIR}/*
suredelete.depends = distclean

QMAKE_EXTRA_TARGETS += suredelete

TRANSLATIONS = \
    $${TARGET}_en_GB.ts \
    $${TARGET}_fr.ts \
    $${TARGET}_it.ts \    
    $${TARGET}_de.ts \
    $${TARGET}_es.ts \
    $${TARGET}.ts

