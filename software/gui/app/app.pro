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
    AlarmSound.qml \
    ControlPanel.qml \
    ModeSelectionPopup.qml \
    controls/AlarmButton.qml \
    controls/parameters/PSUPPParameter.qml \
    controls/parameters/VIVParameter.qml \
    controls/readings/VivDisplay.qml \
    modes/VolumeAssistVentilationMode.qml \
    modes/VolumeControlVentilationMode.qml \
    modes/HighFlowNasalCannulaMode.qml \
    controls/parameters/Flowlmp.qml \
    controls/parameters/Flowlmp.qml \
    controls/parameters/Flowlmp.qml \
    controls/parameters/FiO2Parameter.qml \
    controls/parameters/Flowlmp.qml \
    modes/BIPAP.qml \
    modes/CPAPMode.qml \
    modes/PresureSupportVentilation.qml \
    modes/SyncIMVPC.qml \
    modes/SyncIMVVC.qml \
    modes/PressureRegulatedVolumeControlMode.qml \
    modes/BIPAP.qml \
    modes/BIPAP.qml \
    modes/PressureAssistMode.qml \
    modes/PressureControlMode.qml \
    modes/SpontaneousVentilationModel.qml \
    controls/parameters/PSTEPParameter.qml \
    controls/graphs/FlowGraph.qml \
    controls/graphs/PressureGraph.qml \
    controls/graphs/TvGraph.qml

TRANSLATIONS += ProjectVentilatorGUI_es_GT.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
macx: CONFIG += app_bundle
