/****************************************************************************
** Meta object code from reading C++ file 'deskTopLrcWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../deskTopLrc/deskTopLrcWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'deskTopLrcWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_deskTopLrcWidget_t {
    QByteArrayData data[7];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_deskTopLrcWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_deskTopLrcWidget_t qt_meta_stringdata_deskTopLrcWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "deskTopLrcWidget"
QT_MOC_LITERAL(1, 17, 21), // "slot_currentLrcChange"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 18), // "slot_precentChange"
QT_MOC_LITERAL(4, 59, 6), // "float&"
QT_MOC_LITERAL(5, 66, 4), // "int&"
QT_MOC_LITERAL(6, 71, 8) // "interval"

    },
    "deskTopLrcWidget\0slot_currentLrcChange\0"
    "\0slot_precentChange\0float&\0int&\0"
    "interval"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_deskTopLrcWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x0a /* Public */,
       3,    3,   29,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4, 0x80000000 | 5,    2,    2,    6,

       0        // eod
};

void deskTopLrcWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        deskTopLrcWidget *_t = static_cast<deskTopLrcWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_currentLrcChange((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->slot_precentChange((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject deskTopLrcWidget::staticMetaObject = {
    { &AbsFrameLessAutoSize::staticMetaObject, qt_meta_stringdata_deskTopLrcWidget.data,
      qt_meta_data_deskTopLrcWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *deskTopLrcWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *deskTopLrcWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_deskTopLrcWidget.stringdata0))
        return static_cast<void*>(const_cast< deskTopLrcWidget*>(this));
    return AbsFrameLessAutoSize::qt_metacast(_clname);
}

int deskTopLrcWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsFrameLessAutoSize::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
