DEFINES += GIT_VERSION='"\\\"$$system(git rev-parse HEAD)\\\""'

include( ../defaults.pri )

! include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}

! include( ../src/third_party/qnanopainter/libqnanopainter/include.pri ) {
    error( "Couldn't find the libqnanopainter file!" )
}

QT += core quick serialport multimedia

TEMPLATE = app
TARGET = ProjectVentilatorGUI

SOURCES += main.cpp

LIBS += -L../src -leverything

RESOURCES += qml.qrc images/ sounds/ controls/ fonts/ modes/

DISTFILES += images/Logo.png \
    controls/AlarmButton.qml

TRANSLATIONS += ProjectVentilatorGUI_es_GT.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
macx: CONFIG += app_bundle
