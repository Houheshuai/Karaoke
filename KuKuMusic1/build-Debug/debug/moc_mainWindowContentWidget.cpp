/****************************************************************************
** Meta object code from reading C++ file 'mainWindowContentWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainWindows/mainWindowContentWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainWindowContentWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_playModeWidget_t {
    QByteArrayData data[5];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_playModeWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_playModeWidget_t qt_meta_stringdata_playModeWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "playModeWidget"
QT_MOC_LITERAL(1, 15, 21), // "sig_CurrentModeChange"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 8), // "PlayMode"
QT_MOC_LITERAL(4, 47, 19) // "slot_setCurrentMode"

    },
    "playModeWidget\0sig_CurrentModeChange\0"
    "\0PlayMode\0slot_setCurrentMode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_playModeWidget[] = {

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
       4,    0,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void playModeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        playModeWidget *_t = static_cast<playModeWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_CurrentModeChange((*reinterpret_cast< PlayMode(*)>(_a[1]))); break;
        case 1: _t->slot_setCurrentMode(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (playModeWidget::*_t)(PlayMode );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&playModeWidget::sig_CurrentModeChange)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject playModeWidget::staticMetaObject = {
    { &baseWidget::staticMetaObject, qt_meta_stringdata_playModeWidget.data,
      qt_meta_data_playModeWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *playModeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *playModeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_playModeWidget.stringdata0))
        return static_cast<void*>(const_cast< playModeWidget*>(this));
    return baseWidget::qt_metacast(_clname);
}

int playModeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = baseWidget::qt_metacall(_c, _id, _a);
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
void playModeWidget::sig_CurrentModeChange(PlayMode _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_volSliderWidget_t {
    QByteArrayData data[4];
    char stringdata0[36];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_volSliderWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_volSliderWidget_t qt_meta_stringdata_volSliderWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "volSliderWidget"
QT_MOC_LITERAL(1, 16, 15), // "slot_sliderMove"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 2) // "va"

    },
    "volSliderWidget\0slot_sliderMove\0\0va"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_volSliderWidget[] = {

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

void volSliderWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        volSliderWidget *_t = static_cast<volSliderWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_sliderMove((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject volSliderWidget::staticMetaObject = {
    { &baseWidget::staticMetaObject, qt_meta_stringdata_volSliderWidget.data,
      qt_meta_data_volSliderWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *volSliderWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *volSliderWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_volSliderWidget.stringdata0))
        return static_cast<void*>(const_cast< volSliderWidget*>(this));
    return baseWidget::qt_metacast(_clname);
}

int volSliderWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_AddLoveListTips_t {
    QByteArrayData data[3];
    char stringdata0[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AddLoveListTips_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AddLoveListTips_t qt_meta_stringdata_AddLoveListTips = {
    {
QT_MOC_LITERAL(0, 0, 15), // "AddLoveListTips"
QT_MOC_LITERAL(1, 16, 14), // "slot_timerWork"
QT_MOC_LITERAL(2, 31, 0) // ""

    },
    "AddLoveListTips\0slot_timerWork\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AddLoveListTips[] = {

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

void AddLoveListTips::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AddLoveListTips *_t = static_cast<AddLoveListTips *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_timerWork(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AddLoveListTips::staticMetaObject = {
    { &baseWidget::staticMetaObject, qt_meta_stringdata_AddLoveListTips.data,
      qt_meta_data_AddLoveListTips,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AddLoveListTips::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddLoveListTips::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AddLoveListTips.stringdata0))
        return static_cast<void*>(const_cast< AddLoveListTips*>(this));
    return baseWidget::qt_metacast(_clname);
}

int AddLoveListTips::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
