/****************************************************************************
** Meta object code from reading C++ file 'myshowtablebutton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tableWidgetFiles/myshowtablebutton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myshowtablebutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_myShowTableButton_t {
    QByteArrayData data[12];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myShowTableButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myShowTableButton_t qt_meta_stringdata_myShowTableButton = {
    {
QT_MOC_LITERAL(0, 0, 17), // "myShowTableButton"
QT_MOC_LITERAL(1, 18, 13), // "sig_emptyList"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 15), // "sig_addPlayList"
QT_MOC_LITERAL(4, 49, 11), // "sig_addSong"
QT_MOC_LITERAL(5, 61, 15), // "sig_delPlayList"
QT_MOC_LITERAL(6, 77, 10), // "sig_reName"
QT_MOC_LITERAL(7, 88, 20), // "slot_updateSongCount"
QT_MOC_LITERAL(8, 109, 16), // "slot_menuRequest"
QT_MOC_LITERAL(9, 126, 18), // "slot_returnPressed"
QT_MOC_LITERAL(10, 145, 11), // "slot_ReName"
QT_MOC_LITERAL(11, 157, 13) // "slot_reNameDB"

    },
    "myShowTableButton\0sig_emptyList\0\0"
    "sig_addPlayList\0sig_addSong\0sig_delPlayList\0"
    "sig_reName\0slot_updateSongCount\0"
    "slot_menuRequest\0slot_returnPressed\0"
    "slot_ReName\0slot_reNameDB"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myShowTableButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,
       5,    0,   67,    2, 0x06 /* Public */,
       6,    1,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   71,    2, 0x0a /* Public */,
       8,    0,   72,    2, 0x0a /* Public */,
       9,    0,   73,    2, 0x0a /* Public */,
      10,    0,   74,    2, 0x0a /* Public */,
      11,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void myShowTableButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myShowTableButton *_t = static_cast<myShowTableButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_emptyList(); break;
        case 1: _t->sig_addPlayList(); break;
        case 2: _t->sig_addSong(); break;
        case 3: _t->sig_delPlayList(); break;
        case 4: _t->sig_reName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->slot_updateSongCount(); break;
        case 6: _t->slot_menuRequest(); break;
        case 7: _t->slot_returnPressed(); break;
        case 8: _t->slot_ReName(); break;
        case 9: _t->slot_reNameDB((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (myShowTableButton::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myShowTableButton::sig_emptyList)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (myShowTableButton::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myShowTableButton::sig_addPlayList)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (myShowTableButton::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myShowTableButton::sig_addSong)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (myShowTableButton::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myShowTableButton::sig_delPlayList)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (myShowTableButton::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myShowTableButton::sig_reName)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject myShowTableButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_myShowTableButton.data,
      qt_meta_data_myShowTableButton,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *myShowTableButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myShowTableButton::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_myShowTableButton.stringdata0))
        return static_cast<void*>(const_cast< myShowTableButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int myShowTableButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void myShowTableButton::sig_emptyList()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void myShowTableButton::sig_addPlayList()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void myShowTableButton::sig_addSong()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void myShowTableButton::sig_delPlayList()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void myShowTableButton::sig_reName(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
