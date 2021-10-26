/****************************************************************************
** Meta object code from reading C++ file 'simple_clock.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/src/simple_clock.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simple_clock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SimpleClock_t {
    QByteArrayData data[8];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SimpleClock_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SimpleClock_t qt_meta_stringdata_SimpleClock = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SimpleClock"
QT_MOC_LITERAL(1, 12, 21), // "updateIntervalChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 12), // "time_changed"
QT_MOC_LITERAL(4, 48, 7), // "updated"
QT_MOC_LITERAL(5, 56, 4), // "hour"
QT_MOC_LITERAL(6, 61, 6), // "minute"
QT_MOC_LITERAL(7, 68, 6) // "second"

    },
    "SimpleClock\0updateIntervalChanged\0\0"
    "time_changed\0updated\0hour\0minute\0"
    "second"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SimpleClock[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       3,   32, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,
       4,    0,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       5, QMetaType::Int, 0x00495001,
       6, QMetaType::Int, 0x00495001,
       7, QMetaType::Int, 0x00495001,

 // properties: notify_signal_id
       1,
       1,
       1,

       0        // eod
};

void SimpleClock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SimpleClock *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateIntervalChanged(); break;
        case 1: _t->time_changed(); break;
        case 2: _t->updated(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SimpleClock::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimpleClock::updateIntervalChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SimpleClock::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimpleClock::time_changed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SimpleClock::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimpleClock::updated)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<SimpleClock *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->GetHour(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->GetMinute(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->GetSecond(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject SimpleClock::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_SimpleClock.data,
    qt_meta_data_SimpleClock,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SimpleClock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SimpleClock::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SimpleClock.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SimpleClock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void SimpleClock::updateIntervalChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SimpleClock::time_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SimpleClock::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
