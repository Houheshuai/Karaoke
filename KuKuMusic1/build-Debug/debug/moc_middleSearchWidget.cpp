/****************************************************************************
** Meta object code from reading C++ file 'middleSearchWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../middleWidget/middleSearchWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'middleSearchWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_loadingWidget_t {
    QByteArrayData data[4];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_loadingWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_loadingWidget_t qt_meta_stringdata_loadingWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "loadingWidget"
QT_MOC_LITERAL(1, 14, 16), // "slot_valuechange"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 1) // "i"

    },
    "loadingWidget\0slot_valuechange\0\0i"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_loadingWidget[] = {

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
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void loadingWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        loadingWidget *_t = static_cast<loadingWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_valuechange((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject loadingWidget::staticMetaObject = {
    { &baseWidget::staticMetaObject, qt_meta_stringdata_loadingWidget.data,
      qt_meta_data_loadingWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *loadingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *loadingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_loadingWidget.stringdata0))
        return static_cast<void*>(const_cast< loadingWidget*>(this));
    return baseWidget::qt_metacast(_clname);
}

int loadingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_middleSearchWidget_t {
    QByteArrayData data[15];
    char stringdata0[246];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_middleSearchWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_middleSearchWidget_t qt_meta_stringdata_middleSearchWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "middleSearchWidget"
QT_MOC_LITERAL(1, 19, 23), // "sig_requestSongNextPage"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 20), // "sig_btnPlayClickInfo"
QT_MOC_LITERAL(4, 65, 8), // "songname"
QT_MOC_LITERAL(5, 74, 7), // "songurl"
QT_MOC_LITERAL(6, 82, 3), // "dur"
QT_MOC_LITERAL(7, 86, 19), // "slot_addRequestSong"
QT_MOC_LITERAL(8, 106, 24), // "slot_autoRequestNextPage"
QT_MOC_LITERAL(9, 131, 16), // "slot_requestSong"
QT_MOC_LITERAL(10, 148, 19), // "slot_btnplayclicked"
QT_MOC_LITERAL(11, 168, 18), // "slot_btnaddclicked"
QT_MOC_LITERAL(12, 187, 23), // "slot_btndownloadclicked"
QT_MOC_LITERAL(13, 211, 20), // "slot_checkBoxClicked"
QT_MOC_LITERAL(14, 232, 13) // "slot_menuWork"

    },
    "middleSearchWidget\0sig_requestSongNextPage\0"
    "\0sig_btnPlayClickInfo\0songname\0songurl\0"
    "dur\0slot_addRequestSong\0"
    "slot_autoRequestNextPage\0slot_requestSong\0"
    "slot_btnplayclicked\0slot_btnaddclicked\0"
    "slot_btndownloadclicked\0slot_checkBoxClicked\0"
    "slot_menuWork"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_middleSearchWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    3,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   72,    2, 0x0a /* Public */,
       8,    1,   75,    2, 0x0a /* Public */,
       9,    1,   78,    2, 0x0a /* Public */,
      10,    0,   81,    2, 0x0a /* Public */,
      11,    0,   82,    2, 0x0a /* Public */,
      12,    0,   83,    2, 0x0a /* Public */,
      13,    0,   84,    2, 0x0a /* Public */,
      14,    0,   85,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList, QMetaType::QStringList, QMetaType::QStringList,    4,    5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void middleSearchWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        middleSearchWidget *_t = static_cast<middleSearchWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_requestSongNextPage(); break;
        case 1: _t->sig_btnPlayClickInfo((*reinterpret_cast< const QStringList(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2])),(*reinterpret_cast< const QStringList(*)>(_a[3]))); break;
        case 2: _t->slot_addRequestSong((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 3: _t->slot_autoRequestNextPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slot_requestSong((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 5: _t->slot_btnplayclicked(); break;
        case 6: _t->slot_btnaddclicked(); break;
        case 7: _t->slot_btndownloadclicked(); break;
        case 8: _t->slot_checkBoxClicked(); break;
        case 9: _t->slot_menuWork(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (middleSearchWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&middleSearchWidget::sig_requestSongNextPage)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (middleSearchWidget::*_t)(const QStringList & , const QStringList & , const QStringList & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&middleSearchWidget::sig_btnPlayClickInfo)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject middleSearchWidget::staticMetaObject = {
    { &baseWidget::staticMetaObject, qt_meta_stringdata_middleSearchWidget.data,
      qt_meta_data_middleSearchWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *middleSearchWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *middleSearchWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_middleSearchWidget.stringdata0))
        return static_cast<void*>(const_cast< middleSearchWidget*>(this));
    return baseWidget::qt_metacast(_clname);
}

int middleSearchWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = baseWidget::qt_metacall(_c, _id, _a);
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
void middleSearchWidget::sig_requestSongNextPage()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void middleSearchWidget::sig_btnPlayClickInfo(const QStringList & _t1, const QStringList & _t2, const QStringList & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
