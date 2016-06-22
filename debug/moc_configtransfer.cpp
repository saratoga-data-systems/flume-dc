/****************************************************************************
** Meta object code from reading C++ file 'configtransfer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../configtransfer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'configtransfer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ConfigTransfer_t {
    QByteArrayData data[8];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConfigTransfer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConfigTransfer_t qt_meta_stringdata_ConfigTransfer = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ConfigTransfer"
QT_MOC_LITERAL(1, 15, 8), // "starting"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 9), // "finishing"
QT_MOC_LITERAL(4, 35, 5), // "error"
QT_MOC_LITERAL(5, 41, 6), // "signal"
QT_MOC_LITERAL(6, 48, 4), // "beat"
QT_MOC_LITERAL(7, 53, 5) // "begin"

    },
    "ConfigTransfer\0starting\0\0finishing\0"
    "error\0signal\0beat\0begin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConfigTransfer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    1,   41,    2, 0x06 /* Public */,
       6,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ConfigTransfer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConfigTransfer *_t = static_cast<ConfigTransfer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->starting(); break;
        case 1: _t->finishing(); break;
        case 2: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->beat(); break;
        case 4: _t->begin(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ConfigTransfer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConfigTransfer::starting)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ConfigTransfer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConfigTransfer::finishing)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ConfigTransfer::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConfigTransfer::error)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ConfigTransfer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConfigTransfer::beat)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject ConfigTransfer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ConfigTransfer.data,
      qt_meta_data_ConfigTransfer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ConfigTransfer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConfigTransfer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigTransfer.stringdata0))
        return static_cast<void*>(const_cast< ConfigTransfer*>(this));
    return QObject::qt_metacast(_clname);
}

int ConfigTransfer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ConfigTransfer::starting()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ConfigTransfer::finishing()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void ConfigTransfer::error(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ConfigTransfer::beat()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
