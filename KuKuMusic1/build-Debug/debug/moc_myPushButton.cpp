/****************************************************************************
** Meta object code from reading C++ file 'myPushButton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../absFiles/myPushButton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myPushButton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_myPushButton_t {
    QByteArrayData data[1];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myPushButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myPushButton_t qt_meta_stringdata_myPushButton = {
    {
QT_MOC_LITERAL(0, 0, 12) // "myPushButton"

    },
    "myPushButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myPushButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void myPushButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject myPushButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_myPushButton.data,
      qt_meta_data_myPushButton,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *myPushButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myPushButton::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_myPushButton.stringdata0))
        return static_cast<void*>(const_cast< myPushButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int myPushButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_volButton_t {
    QByteArrayData data[4];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_volButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_volButton_t qt_meta_stringdata_volButton = {
    {
QT_MOC_LITERAL(0, 0, 9), // "volButton"
QT_MOC_LITERAL(1, 10, 7), // "setMute"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 15) // "setButtonPixmap"

    },
    "volButton\0setMute\0\0setButtonPixmap"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_volButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void volButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        volButton *_t = static_cast<volButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setMute((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setButtonPixmap((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (volButton::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&volButton::setMute)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject volButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_volButton.data,
      qt_meta_data_volButton,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *volButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *volButton::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_volButton.stringdata0))
        return static_cast<void*>(const_cast< volButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int volButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void volButton::setMute(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_volButton2_t {
    QByteArrayData data[5];
    char stringdata0[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_volButton2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_volButton2_t qt_meta_stringdata_volButton2 = {
    {
QT_MOC_LITERAL(0, 0, 10), // "volButton2"
QT_MOC_LITERAL(1, 11, 7), // "setMute"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 17), // "sig_hideVolWidget"
QT_MOC_LITERAL(4, 38, 15) // "setButtonPixmap"

    },
    "volButton2\0setMute\0\0sig_hideVolWidget\0"
    "setButtonPixmap"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_volButton2[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       3,    0,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void volButton2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        volButton2 *_t = static_cast<volButton2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setMute((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sig_hideVolWidget(); break;
        case 2: _t->setButtonPixmap((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (volButton2::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&volButton2::setMute)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (volButton2::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&volButton2::sig_hideVolWidget)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject volButton2::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_volButton2.data,
      qt_meta_data_volButton2,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *volButton2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *volButton2::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_volButton2.stringdata0))
        return static_cast<void*>(const_cast< volButton2*>(this));
    return QPushButton::qt_metacast(_clname);
}

int volButton2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
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
    return _id;
}

// SIGNAL 0
void volButton2::setMute(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void volButton2::sig_hideVolWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
struct qt_meta_stringdata_stackButton_t {
    QByteArrayData data[1];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_stackButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_stackButton_t qt_meta_stringdata_stackButton = {
    {
QT_MOC_LITERAL(0, 0, 11) // "stackButton"

    },
    "stackButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_stackButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void stackButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject stackButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_stackButton.data,
      qt_meta_data_stackButton,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *stackButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stackButton::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_stackButton.stringdata0))
        return static_cast<void*>(const_cast< stackButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int stackButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_leftPixButton_t {
    QByteArrayData data[1];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_leftPixButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_leftPixButton_t qt_meta_stringdata_leftPixButton = {
    {
QT_MOC_LITERAL(0, 0, 13) // "leftPixButton"

    },
    "leftPixButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_leftPixButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void leftPixButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject leftPixButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_leftPixButton.data,
      qt_meta_data_leftPixButton,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *leftPixButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *leftPixButton::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_leftPixButton.stringdata0))
        return static_cast<void*>(const_cast< leftPixButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int leftPixButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_playModeButton_t {
    QByteArrayData data[1];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_playModeButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_playModeButton_t qt_meta_stringdata_playModeButton = {
    {
QT_MOC_LITERAL(0, 0, 14) // "playModeButton"

    },
    "playModeButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_playModeButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void playModeButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject playModeButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_playModeButton.data,
      qt_meta_data_playModeButton,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *playModeButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *playModeButton::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_playModeButton.stringdata0))
        return static_cast<void*>(const_cast< playModeButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int playModeButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_playingWidgetBtn_t {
    QByteArrayData data[1];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_playingWidgetBtn_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_playingWidgetBtn_t qt_meta_stringdata_playingWidgetBtn = {
    {
QT_MOC_LITERAL(0, 0, 16) // "playingWidgetBtn"

    },
    "playingWidgetBtn"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_playingWidgetBtn[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void playingWidgetBtn::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject playingWidgetBtn::staticMetaObject = {
    { &myPushButton::staticMetaObject, qt_meta_stringdata_playingWidgetBtn.data,
      qt_meta_data_playingWidgetBtn,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *playingWidgetBtn::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *playingWidgetBtn::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_playingWidgetBtn.stringdata0))
        return static_cast<void*>(const_cast< playingWidgetBtn*>(this));
    return myPushButton::qt_metacast(_clname);
}

int playingWidgetBtn::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = myPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
