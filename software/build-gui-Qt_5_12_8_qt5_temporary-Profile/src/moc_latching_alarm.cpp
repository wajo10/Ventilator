/****************************************************************************
** Meta object code from reading C++ file 'latching_alarm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/src/latching_alarm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'latching_alarm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AlarmPriority_t {
    QByteArrayData data[6];
    char stringdata0[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AlarmPriority_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AlarmPriority_t qt_meta_stringdata_AlarmPriority = {
    {
QT_MOC_LITERAL(0, 0, 13), // "AlarmPriority"
QT_MOC_LITERAL(1, 14, 4), // "Enum"
QT_MOC_LITERAL(2, 19, 4), // "NONE"
QT_MOC_LITERAL(3, 24, 3), // "LOW"
QT_MOC_LITERAL(4, 28, 6), // "MEDIUM"
QT_MOC_LITERAL(5, 35, 4) // "HIGH"

    },
    "AlarmPriority\0Enum\0NONE\0LOW\0MEDIUM\0"
    "HIGH"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AlarmPriority[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    4,   19,

 // enum data: key, value
       2, uint(AlarmPriority::NONE),
       3, uint(AlarmPriority::LOW),
       4, uint(AlarmPriority::MEDIUM),
       5, uint(AlarmPriority::HIGH),

       0        // eod
};

QT_INIT_METAOBJECT const QMetaObject AlarmPriority::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_AlarmPriority.data,
    qt_meta_data_AlarmPriority,
    nullptr,
    nullptr,
    nullptr
} };

struct qt_meta_stringdata_LatchingAlarm_t {
    QByteArrayData data[9];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LatchingAlarm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LatchingAlarm_t qt_meta_stringdata_LatchingAlarm = {
    {
QT_MOC_LITERAL(0, 0, 13), // "LatchingAlarm"
QT_MOC_LITERAL(1, 14, 7), // "updated"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 15), // "nominalPriority"
QT_MOC_LITERAL(4, 39, 19), // "AlarmPriority::Enum"
QT_MOC_LITERAL(5, 59, 23), // "effectiveVisualPriority"
QT_MOC_LITERAL(6, 83, 22), // "effectiveAudioPriority"
QT_MOC_LITERAL(7, 106, 10), // "bannerText"
QT_MOC_LITERAL(8, 117, 18) // "remainingSilenceMs"

    },
    "LatchingAlarm\0updated\0\0nominalPriority\0"
    "AlarmPriority::Enum\0effectiveVisualPriority\0"
    "effectiveAudioPriority\0bannerText\0"
    "remainingSilenceMs"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LatchingAlarm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       5,   20, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // properties: name, type, flags
       3, 0x80000000 | 4, 0x00095409,
       5, 0x80000000 | 4, 0x00495009,
       6, 0x80000000 | 4, 0x00495009,
       7, QMetaType::QString, 0x00495001,
       8, QMetaType::Int, 0x00495001,

 // properties: notify_signal_id
       0,
       0,
       0,
       0,
       0,

       0        // eod
};

void LatchingAlarm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LatchingAlarm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updated(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LatchingAlarm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LatchingAlarm::updated)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<LatchingAlarm *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< AlarmPriority::Enum*>(_v) = _t->GetNominalPriority(); break;
        case 1: *reinterpret_cast< AlarmPriority::Enum*>(_v) = _t->GetEffectiveVisualPriority(); break;
        case 2: *reinterpret_cast< AlarmPriority::Enum*>(_v) = _t->GetEffectiveAudioPriority(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->GetBannerText(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->GetRemainingSilenceMs(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

static const QMetaObject * const qt_meta_extradata_LatchingAlarm[] = {
        &AlarmPriority::staticMetaObject,
    nullptr
};

QT_INIT_METAOBJECT const QMetaObject LatchingAlarm::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_LatchingAlarm.data,
    qt_meta_data_LatchingAlarm,
    qt_static_metacall,
    qt_meta_extradata_LatchingAlarm,
    nullptr
} };


const QMetaObject *LatchingAlarm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LatchingAlarm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LatchingAlarm.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LatchingAlarm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void LatchingAlarm::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
