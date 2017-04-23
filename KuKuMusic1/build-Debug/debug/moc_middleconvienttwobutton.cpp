/****************************************************************************
** Meta object code from reading C++ file 'middleconvienttwobutton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../middleWidget/middleconvienttwobutton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'middleconvienttwobutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_middleConvientTwoButton_t {
    QByteArrayData data[3];
    char stringdata0[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_middleConvientTwoButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_middleConvientTwoButton_t qt_meta_stringdata_middleConvientTwoButton = {
    {
QT_MOC_LITERAL(0, 0, 23), // "middleConvientTwoButton"
QT_MOC_LITERAL(1, 24, 15), // "slot_timerEvent"
QT_MOC_LITERAL(2, 40, 0) // ""

    },
    "middleConvientTwoButton\0slot_timerEvent\0"
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_middleConvientTwoButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void middleConvientTwoButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        middleConvientTwoButton *_t = static_cast<middleConvientTwoButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_timerEvent(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject middleConvientTwoButton::staticMetaObject = {
    { &baseWidget::staticMetaObject, qt_meta_stringdata_middleConvientTwoButton.data,
      qt_meta_data_middleConvientTwoButton,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *middleConvientTwoButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *middleConvientTwoButton::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_middleConvientTwoButton.stringdata0))
        return static_cast<void*>(const_cast< middleConvientTwoButton*>(this));
    return baseWidget::qt_metacast(_clname);
}

int middleConvientTwoButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = baseWidget::qt_metacall(_c, _id, _a);
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
    return _id;
}
struct qt_meta_stringdata_middleListSearch_t {
    QByteArrayData data[3];
    char stringdata0[27];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_middleListSearch_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_middleListSearch_t qt_meta_stringdata_middleListSearch = {
    {
QT_MOC_LITERAL(0, 0, 16), // "middleListSearch"
QT_MOC_LITERAL(1, 17, 8), // "setClear"
QT_MOC_LITERAL(2, 26, 0) // ""

    },
    "middleListSearch\0setClear\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_middleListSearch[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void middleListSearch::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        middleListSearch *_t = static_cast<middleListSearch *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setClear(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject middleListSearch::staticMetaObject = {
    { &baseWidget::staticMetaObject, qt_meta_stringdata_middleListSearch.data,
      qt_meta_data_middleListSearch,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *middleListSearch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *middleListSearch::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_middleListSearch.stringdata0))
        return static_cast<void*>(const_cast< middleListSearch*>(this));
    return baseWidget::qt_metacast(_clname);
}

int middleListSearch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = baseWidget::qt_metacall(_c, _id, _a);
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
    return _id;
}
QT_END_MOC_NAMESPACE
