/****************************************************************************
** Meta object code from reading C++ file 'gui_state_container.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/src/gui_state_container.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui_state_container.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GuiStateContainer_t {
    QByteArrayData data[46];
    char stringdata0[715];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GuiStateContainer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GuiStateContainer_t qt_meta_stringdata_GuiStateContainer = {
    {
QT_MOC_LITERAL(0, 0, 17), // "GuiStateContainer"
QT_MOC_LITERAL(1, 18, 20), // "measurements_changed"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 14), // "params_changed"
QT_MOC_LITERAL(4, 55, 26), // "battery_percentage_changed"
QT_MOC_LITERAL(5, 82, 13), // "clock_changed"
QT_MOC_LITERAL(6, 96, 21), // "PressureSeriesChanged"
QT_MOC_LITERAL(7, 118, 17), // "FlowSeriesChanged"
QT_MOC_LITERAL(8, 136, 18), // "TidalSeriesChanged"
QT_MOC_LITERAL(9, 155, 19), // "IsDebugBuildChanged"
QT_MOC_LITERAL(10, 175, 19), // "AlarmManagerChanged"
QT_MOC_LITERAL(11, 195, 25), // "controller_status_changed"
QT_MOC_LITERAL(12, 221, 13), // "SteadyInstant"
QT_MOC_LITERAL(13, 235, 3), // "now"
QT_MOC_LITERAL(14, 239, 16), // "ControllerStatus"
QT_MOC_LITERAL(15, 256, 6), // "status"
QT_MOC_LITERAL(16, 263, 12), // "UpdateGraphs"
QT_MOC_LITERAL(17, 276, 18), // "is_using_fake_data"
QT_MOC_LITERAL(18, 295, 17), // "measured_pressure"
QT_MOC_LITERAL(19, 313, 13), // "measured_flow"
QT_MOC_LITERAL(20, 327, 11), // "measured_tv"
QT_MOC_LITERAL(21, 339, 11), // "measured_rr"
QT_MOC_LITERAL(22, 351, 13), // "measured_peep"
QT_MOC_LITERAL(23, 365, 12), // "measured_pip"
QT_MOC_LITERAL(24, 378, 12), // "measured_ier"
QT_MOC_LITERAL(25, 391, 21), // "measured_fio2_percent"
QT_MOC_LITERAL(26, 413, 14), // "pressureSeries"
QT_MOC_LITERAL(27, 428, 16), // "QVector<QPointF>"
QT_MOC_LITERAL(28, 445, 10), // "flowSeries"
QT_MOC_LITERAL(29, 456, 11), // "tidalSeries"
QT_MOC_LITERAL(30, 468, 12), // "alarmManager"
QT_MOC_LITERAL(31, 481, 13), // "AlarmManager*"
QT_MOC_LITERAL(32, 495, 14), // "commanded_mode"
QT_MOC_LITERAL(33, 510, 15), // "VentilationMode"
QT_MOC_LITERAL(34, 526, 12), // "commanded_rr"
QT_MOC_LITERAL(35, 539, 14), // "commanded_peep"
QT_MOC_LITERAL(36, 554, 13), // "commanded_pip"
QT_MOC_LITERAL(37, 568, 16), // "commanded_i_time"
QT_MOC_LITERAL(38, 585, 22), // "commanded_fio2_percent"
QT_MOC_LITERAL(39, 608, 17), // "batteryPercentage"
QT_MOC_LITERAL(40, 626, 5), // "clock"
QT_MOC_LITERAL(41, 632, 12), // "SimpleClock*"
QT_MOC_LITERAL(42, 645, 12), // "isDebugBuild"
QT_MOC_LITERAL(43, 658, 16), // "PRESSURE_CONTROL"
QT_MOC_LITERAL(44, 675, 15), // "PRESSURE_ASSIST"
QT_MOC_LITERAL(45, 691, 23) // "HIGH_FLOW_NASAL_CANNULA"

    },
    "GuiStateContainer\0measurements_changed\0"
    "\0params_changed\0battery_percentage_changed\0"
    "clock_changed\0PressureSeriesChanged\0"
    "FlowSeriesChanged\0TidalSeriesChanged\0"
    "IsDebugBuildChanged\0AlarmManagerChanged\0"
    "controller_status_changed\0SteadyInstant\0"
    "now\0ControllerStatus\0status\0UpdateGraphs\0"
    "is_using_fake_data\0measured_pressure\0"
    "measured_flow\0measured_tv\0measured_rr\0"
    "measured_peep\0measured_pip\0measured_ier\0"
    "measured_fio2_percent\0pressureSeries\0"
    "QVector<QPointF>\0flowSeries\0tidalSeries\0"
    "alarmManager\0AlarmManager*\0commanded_mode\0"
    "VentilationMode\0commanded_rr\0"
    "commanded_peep\0commanded_pip\0"
    "commanded_i_time\0commanded_fio2_percent\0"
    "batteryPercentage\0clock\0SimpleClock*\0"
    "isDebugBuild\0PRESSURE_CONTROL\0"
    "PRESSURE_ASSIST\0HIGH_FLOW_NASAL_CANNULA"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GuiStateContainer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
      22,   84, // properties
       1,  172, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,
       5,    0,   72,    2, 0x06 /* Public */,
       6,    0,   73,    2, 0x06 /* Public */,
       7,    0,   74,    2, 0x06 /* Public */,
       8,    0,   75,    2, 0x06 /* Public */,
       9,    0,   76,    2, 0x06 /* Public */,
      10,    0,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    2,   78,    2, 0x0a /* Public */,
      16,    0,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 14,   13,   15,
    QMetaType::Void,

 // properties: name, type, flags
      17, QMetaType::Bool, 0x00095401,
      18, QMetaType::QReal, 0x00495001,
      19, QMetaType::QReal, 0x00495001,
      20, QMetaType::QReal, 0x00495001,
      21, QMetaType::UInt, 0x00495001,
      22, QMetaType::UInt, 0x00495001,
      23, QMetaType::UInt, 0x00495001,
      24, QMetaType::QReal, 0x00495001,
      25, QMetaType::QReal, 0x00495001,
      26, 0x80000000 | 27, 0x00495009,
      28, 0x80000000 | 27, 0x00495009,
      29, 0x80000000 | 27, 0x00495009,
      30, 0x80000000 | 31, 0x00495009,
      32, 0x80000000 | 33, 0x0049500b,
      34, QMetaType::UInt, 0x00495003,
      35, QMetaType::UInt, 0x00495003,
      36, QMetaType::UInt, 0x00495003,
      37, QMetaType::QReal, 0x00495003,
      38, QMetaType::QReal, 0x00495003,
      39, QMetaType::Int, 0x00495001,
      40, 0x80000000 | 41, 0x00495009,
      42, QMetaType::Bool, 0x00495001,

 // properties: notify_signal_id
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       4,
       5,
       6,
       8,
       1,
       1,
       1,
       1,
       1,
       1,
       2,
       3,
       7,

 // enums: name, alias, flags, count, data
      33,   33, 0x0,    3,  177,

 // enum data: key, value
      43, uint(GuiStateContainer::PRESSURE_CONTROL),
      44, uint(GuiStateContainer::PRESSURE_ASSIST),
      45, uint(GuiStateContainer::HIGH_FLOW_NASAL_CANNULA),

       0        // eod
};

void GuiStateContainer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GuiStateContainer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->measurements_changed(); break;
        case 1: _t->params_changed(); break;
        case 2: _t->battery_percentage_changed(); break;
        case 3: _t->clock_changed(); break;
        case 4: _t->PressureSeriesChanged(); break;
        case 5: _t->FlowSeriesChanged(); break;
        case 6: _t->TidalSeriesChanged(); break;
        case 7: _t->IsDebugBuildChanged(); break;
        case 8: _t->AlarmManagerChanged(); break;
        case 9: _t->controller_status_changed((*reinterpret_cast< SteadyInstant(*)>(_a[1])),(*reinterpret_cast< const ControllerStatus(*)>(_a[2]))); break;
        case 10: _t->UpdateGraphs(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GuiStateContainer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiStateContainer::measurements_changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GuiStateContainer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiStateContainer::params_changed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GuiStateContainer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiStateContainer::battery_percentage_changed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GuiStateContainer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiStateContainer::clock_changed)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GuiStateContainer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiStateContainer::PressureSeriesChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GuiStateContainer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiStateContainer::FlowSeriesChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GuiStateContainer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiStateContainer::TidalSeriesChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (GuiStateContainer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiStateContainer::IsDebugBuildChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (GuiStateContainer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiStateContainer::AlarmManagerChanged)) {
                *result = 8;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 12:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< AlarmManager* >(); break;
        case 11:
        case 10:
        case 9:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QPointF> >(); break;
        case 20:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< SimpleClock* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<GuiStateContainer *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->get_is_using_fake_data(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = _t->get_measured_pressure(); break;
        case 2: *reinterpret_cast< qreal*>(_v) = _t->get_measured_flow(); break;
        case 3: *reinterpret_cast< qreal*>(_v) = _t->get_measured_tv(); break;
        case 4: *reinterpret_cast< quint32*>(_v) = _t->get_measured_rr(); break;
        case 5: *reinterpret_cast< quint32*>(_v) = _t->get_measured_peep(); break;
        case 6: *reinterpret_cast< quint32*>(_v) = _t->get_measured_pip(); break;
        case 7: *reinterpret_cast< qreal*>(_v) = _t->get_measured_ier(); break;
        case 8: *reinterpret_cast< qreal*>(_v) = _t->get_measured_fio2_percent(); break;
        case 9: *reinterpret_cast< QVector<QPointF>*>(_v) = _t->GetPressureSeries(); break;
        case 10: *reinterpret_cast< QVector<QPointF>*>(_v) = _t->GetFlowSeries(); break;
        case 11: *reinterpret_cast< QVector<QPointF>*>(_v) = _t->GetTidalSeries(); break;
        case 12: *reinterpret_cast< AlarmManager**>(_v) = _t->GetAlarmManager(); break;
        case 13: *reinterpret_cast< VentilationMode*>(_v) = _t->commanded_mode_; break;
        case 14: *reinterpret_cast< quint32*>(_v) = _t->commanded_rr_; break;
        case 15: *reinterpret_cast< quint32*>(_v) = _t->commanded_peep_; break;
        case 16: *reinterpret_cast< quint32*>(_v) = _t->commanded_pip_; break;
        case 17: *reinterpret_cast< qreal*>(_v) = _t->commanded_i_time_; break;
        case 18: *reinterpret_cast< qreal*>(_v) = _t->commanded_fio2_percent_; break;
        case 19: *reinterpret_cast< int*>(_v) = _t->get_battery_percentage(); break;
        case 20: *reinterpret_cast< SimpleClock**>(_v) = _t->get_clock(); break;
        case 21: *reinterpret_cast< bool*>(_v) = _t->IsDebugBuild(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<GuiStateContainer *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 13:
            if (_t->commanded_mode_ != *reinterpret_cast< VentilationMode*>(_v)) {
                _t->commanded_mode_ = *reinterpret_cast< VentilationMode*>(_v);
                Q_EMIT _t->params_changed();
            }
            break;
        case 14:
            if (_t->commanded_rr_ != *reinterpret_cast< quint32*>(_v)) {
                _t->commanded_rr_ = *reinterpret_cast< quint32*>(_v);
                Q_EMIT _t->params_changed();
            }
            break;
        case 15:
            if (_t->commanded_peep_ != *reinterpret_cast< quint32*>(_v)) {
                _t->commanded_peep_ = *reinterpret_cast< quint32*>(_v);
                Q_EMIT _t->params_changed();
            }
            break;
        case 16:
            if (_t->commanded_pip_ != *reinterpret_cast< quint32*>(_v)) {
                _t->commanded_pip_ = *reinterpret_cast< quint32*>(_v);
                Q_EMIT _t->params_changed();
            }
            break;
        case 17:
            if (_t->commanded_i_time_ != *reinterpret_cast< qreal*>(_v)) {
                _t->commanded_i_time_ = *reinterpret_cast< qreal*>(_v);
                Q_EMIT _t->params_changed();
            }
            break;
        case 18:
            if (_t->commanded_fio2_percent_ != *reinterpret_cast< qreal*>(_v)) {
                _t->commanded_fio2_percent_ = *reinterpret_cast< qreal*>(_v);
                Q_EMIT _t->params_changed();
            }
            break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject GuiStateContainer::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_GuiStateContainer.data,
    qt_meta_data_GuiStateContainer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GuiStateContainer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GuiStateContainer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GuiStateContainer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GuiStateContainer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 22;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void GuiStateContainer::measurements_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void GuiStateContainer::params_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void GuiStateContainer::battery_percentage_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void GuiStateContainer::clock_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void GuiStateContainer::PressureSeriesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void GuiStateContainer::FlowSeriesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void GuiStateContainer::TidalSeriesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void GuiStateContainer::IsDebugBuildChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void GuiStateContainer::AlarmManagerChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
