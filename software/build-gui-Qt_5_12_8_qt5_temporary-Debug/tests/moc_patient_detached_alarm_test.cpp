/****************************************************************************
** Meta object code from reading C++ file 'patient_detached_alarm_test.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/tests/patient_detached_alarm_test.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'patient_detached_alarm_test.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PatientDetachedAlarmTest_t {
    QByteArrayData data[9];
    char stringdata0[206];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PatientDetachedAlarmTest_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PatientDetachedAlarmTest_t qt_meta_stringdata_PatientDetachedAlarmTest = {
    {
QT_MOC_LITERAL(0, 0, 24), // "PatientDetachedAlarmTest"
QT_MOC_LITERAL(1, 25, 12), // "initTestCase"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 15), // "cleanupTestCase"
QT_MOC_LITERAL(4, 55, 22), // "testZeroFlowCorrection"
QT_MOC_LITERAL(5, 78, 31), // "testSmallPositiveFlowCorrection"
QT_MOC_LITERAL(6, 110, 31), // "testSmallNegativeFlowCorrection"
QT_MOC_LITERAL(7, 142, 31), // "testLargePositiveFlowCorrection"
QT_MOC_LITERAL(8, 174, 31) // "testLargeNegativeFlowCorrection"

    },
    "PatientDetachedAlarmTest\0initTestCase\0"
    "\0cleanupTestCase\0testZeroFlowCorrection\0"
    "testSmallPositiveFlowCorrection\0"
    "testSmallNegativeFlowCorrection\0"
    "testLargePositiveFlowCorrection\0"
    "testLargeNegativeFlowCorrection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PatientDetachedAlarmTest[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PatientDetachedAlarmTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PatientDetachedAlarmTest *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->cleanupTestCase(); break;
        case 2: _t->testZeroFlowCorrection(); break;
        case 3: _t->testSmallPositiveFlowCorrection(); break;
        case 4: _t->testSmallNegativeFlowCorrection(); break;
        case 5: _t->testLargePositiveFlowCorrection(); break;
        case 6: _t->testLargeNegativeFlowCorrection(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject PatientDetachedAlarmTest::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_PatientDetachedAlarmTest.data,
    qt_meta_data_PatientDetachedAlarmTest,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PatientDetachedAlarmTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PatientDetachedAlarmTest::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PatientDetachedAlarmTest.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PatientDetachedAlarmTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
