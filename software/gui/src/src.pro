QT += core quick serialport qml multimedia

include( ../defaults.pri )
! include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}


! include( third_party/qnanopainter/libqnanopainter/include.pri ) {
    error( "Couldn't find the libqnanopainter file!" )
}

TARGET = everything
TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
  alarm.h \
  alarm_manager.h \
  chrono.h \
  connected_device.h \
  controller_history.h \
  gui_state_container.h \
  latching_alarm.h \
  patient_detached_alarm.h \
  periodic_closure.h \
  pip_exceeded_alarm.h \
  pip_not_reached_alarm.h \
  respira_connected_device.h \
  simple_clock.h \
  time_series_graph.h \
  time_series_graph_painter.h \
  logger.h

SOURCES += gui_state_container.cpp \
  periodic_closure.cpp \
  time_series_graph_painter.cpp \
  logger.cpp
