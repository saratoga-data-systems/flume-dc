/****************************************************************************
** Meta object code from reading C++ file 'flumesettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../flumesettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flumesettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FlumeSettings_t {
    QByteArrayData data[10];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FlumeSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FlumeSettings_t qt_meta_stringdata_FlumeSettings = {
    {
QT_MOC_LITERAL(0, 0, 13), // "FlumeSettings"
QT_MOC_LITERAL(1, 14, 6), // "remove"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "tabIndex"
QT_MOC_LITERAL(4, 31, 4), // "name"
QT_MOC_LITERAL(5, 36, 10), // "saveServer"
QT_MOC_LITERAL(6, 47, 10), // "emitRemove"
QT_MOC_LITERAL(7, 58, 5), // "reset"
QT_MOC_LITERAL(8, 64, 12), // "verifyServer"
QT_MOC_LITERAL(9, 77, 10) // "invalidate"

    },
    "FlumeSettings\0remove\0\0tabIndex\0name\0"
    "saveServer\0emitRemove\0reset\0verifyServer\0"
    "invalidate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlumeSettings[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   49,    2, 0x0a /* Public */,
       6,    0,   50,    2, 0x0a /* Public */,
       7,    0,   51,    2, 0x0a /* Public */,
       8,    0,   52,    2, 0x0a /* Public */,
       9,    0,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FlumeSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FlumeSettings *_t = static_cast<FlumeSettings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->remove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->saveServer(); break;
        case 2: _t->emitRemove(); break;
        case 3: _t->reset(); break;
        case 4: _t->verifyServer(); break;
        case 5: _t->invalidate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FlumeSettings::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FlumeSettings::remove)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject FlumeSettings::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FlumeSettings.data,
      qt_meta_data_FlumeSettings,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FlumeSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlumeSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FlumeSettings.stringdata0))
        return static_cast<void*>(const_cast< FlumeSettings*>(this));
    return QWidget::qt_metacast(_clname);
}

int FlumeSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void FlumeSettings::remove(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
