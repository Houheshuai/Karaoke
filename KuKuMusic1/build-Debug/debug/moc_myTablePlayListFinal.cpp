/****************************************************************************
** Meta object code from reading C++ file 'myTablePlayListFinal.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tableWidgetFiles/myTablePlayListFinal.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myTablePlayListFinal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_myTablePlayListFinal_t {
    QByteArrayData data[11];
    char stringdata0[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myTablePlayListFinal_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myTablePlayListFinal_t qt_meta_stringdata_myTablePlayListFinal = {
    {
QT_MOC_LITERAL(0, 0, 20), // "myTablePlayListFinal"
QT_MOC_LITERAL(1, 21, 14), // "slot_emptyList"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 18), // "slot_showHideTable"
QT_MOC_LITERAL(4, 56, 12), // "slot_addSong"
QT_MOC_LITERAL(5, 69, 18), // "slot_addSongFolder"
QT_MOC_LITERAL(6, 88, 27), // "slot_addSongFromSearchTable"
QT_MOC_LITERAL(7, 116, 4), // "name"
QT_MOC_LITERAL(8, 121, 3), // "url"
QT_MOC_LITERAL(9, 125, 3), // "dur"
QT_MOC_LITERAL(10, 129, 28) // "slot_playSongFromSearchTable"

    },
    "myTablePlayListFinal\0slot_emptyList\0"
    "\0slot_showHideTable\0slot_addSong\0"
    "slot_addSongFolder\0slot_addSongFromSearchTable\0"
    "name\0url\0dur\0slot_playSongFromSearchTable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myTablePlayListFinal[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    3,   48,    2, 0x0a /* Public */,
      10,    3,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList, QMetaType::QStringList, QMetaType::QStringList,    7,    8,    9,
    QMetaType::Void, QMetaType::QStringList, QMetaType::QStringList, QMetaType::QStringList,    7,    8,    9,

       0        // eod
};

void myTablePlayListFinal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myTablePlayListFinal *_t = static_cast<myTablePlayListFinal *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_emptyList(); break;
        case 1: _t->slot_showHideTable(); break;
        case 2: _t->slot_addSong(); break;
        case 3: _t->slot_addSongFolder(); break;
        case 4: _t->slot_addSongFromSearchTable((*reinterpret_cast< const QStringList(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2])),(*reinterpret_cast< const QStringList(*)>(_a[3]))); break;
        case 5: _t->slot_playSongFromSearchTable((*reinterpret_cast< const QStringList(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2])),(*reinterpret_cast< const QStringList(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject myTablePlayListFinal::staticMetaObject = {
    { &baseWidget::staticMetaObject, qt_meta_stringdata_myTablePlayListFinal.data,
      qt_meta_data_myTablePlayListFinal,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *myTablePlayListFinal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myTablePlayListFinal::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_myTablePlayListFinal.stringdata0))
        return static_cast<void*>(const_cast< myTablePlayListFinal*>(this));
    return baseWidget::qt_metacast(_clname);
}

int myTablePlayListFinal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = baseWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
