/****************************************************************************
** Meta object code from reading C++ file 'middlewidgetleft.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../middleWidget/middlewidgetleft.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'middlewidgetleft.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_middleWidgetLeft_t {
    QByteArrayData data[8];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_middleWidgetLeft_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_middleWidgetLeft_t qt_meta_stringdata_middleWidgetLeft = {
    {
QT_MOC_LITERAL(0, 0, 16), // "middleWidgetLeft"
QT_MOC_LITERAL(1, 17, 8), // "slot_btn"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 16), // "setWidgetOpacity"
QT_MOC_LITERAL(4, 44, 25), // "slot_changeButtonSelected"
QT_MOC_LITERAL(5, 70, 1), // "i"
QT_MOC_LITERAL(6, 72, 13), // "slot_finished"
QT_MOC_LITERAL(7, 86, 3) // "m_x"

    },
    "middleWidgetLeft\0slot_btn\0\0setWidgetOpacity\0"
    "slot_changeButtonSelected\0i\0slot_finished\0"
    "m_x"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_middleWidgetLeft[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       1,   42, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    1,   35,    2, 0x08 /* Private */,
       4,    1,   38,    2, 0x08 /* Private */,
       6,    0,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,

 // properties: name, type, flags
       7, QMetaType::Int, 0x00095003,

       0        // eod
};

void middleWidgetLeft::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        middleWidgetLeft *_t = static_cast<middleWidgetLeft *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_btn(); break;
        case 1: _t->setWidgetOpacity((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_changeButtonSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slot_finished(); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        middleWidgetLeft *_t = static_cast<middleWidgetLeft *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->getValue(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        middleWidgetLeft *_t = static_cast<middleWidgetLeft *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->animation(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject middleWidgetLeft::staticMetaObject = {
    { &baseWidget::staticMetaObject, qt_meta_stringdata_middleWidgetLeft.data,
      qt_meta_data_middleWidgetLeft,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *middleWidgetLeft::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *middleWidgetLeft::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_middleWidgetLeft.stringdata0))
        return static_cast<void*>(const_cast< middleWidgetLeft*>(this));
    return baseWidget::qt_metacast(_clname);
}

int middleWidgetLeft::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = baseWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
