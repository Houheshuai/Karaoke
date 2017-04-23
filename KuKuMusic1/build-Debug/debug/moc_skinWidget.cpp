/****************************************************************************
** Meta object code from reading C++ file 'skinWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../otherWidget/skinWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'skinWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_skinWidgetContentItem_t {
    QByteArrayData data[3];
    char stringdata0[31];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_skinWidgetContentItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_skinWidgetContentItem_t qt_meta_stringdata_skinWidgetContentItem = {
    {
QT_MOC_LITERAL(0, 0, 21), // "skinWidgetContentItem"
QT_MOC_LITERAL(1, 22, 7), // "clicked"
QT_MOC_LITERAL(2, 30, 0) // ""

    },
    "skinWidgetContentItem\0clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_skinWidgetContentItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void skinWidgetContentItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        skinWidgetContentItem *_t = static_cast<skinWidgetContentItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (skinWidgetContentItem::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&skinWidgetContentItem::clicked)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject skinWidgetContentItem::staticMetaObject = {
    { &baseWidget::staticMetaObject, qt_meta_stringdata_skinWidgetContentItem.data,
      qt_meta_data_skinWidgetContentItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *skinWidgetContentItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *skinWidgetContentItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_skinWidgetContentItem.stringdata0))
        return static_cast<void*>(const_cast< skinWidgetContentItem*>(this));
    return baseWidget::qt_metacast(_clname);
}

int skinWidgetContentItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void skinWidgetContentItem::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
struct qt_meta_stringdata_skinContentWidget_t {
    QByteArrayData data[4];
    char stringdata0[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_skinContentWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_skinContentWidget_t qt_meta_stringdata_skinContentWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "skinContentWidget"
QT_MOC_LITERAL(1, 18, 17), // "sig_setBackground"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 16) // "slot_itemClicked"

    },
    "skinContentWidget\0sig_setBackground\0"
    "\0slot_itemClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_skinContentWidget[] = {

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
       3,    0,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void skinContentWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        skinContentWidget *_t = static_cast<skinContentWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_setBackground((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->slot_itemClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (skinContentWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&skinContentWidget::sig_setBackground)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject skinContentWidget::staticMetaObject = {
    { &baseWidget::staticMetaObject, qt_meta_stringdata_skinContentWidget.data,
      qt_meta_data_skinContentWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *skinContentWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *skinContentWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_skinContentWidget.stringdata0))
        return static_cast<void*>(const_cast< skinContentWidget*>(this));
    return baseWidget::qt_metacast(_clname);
}

int skinContentWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void skinContentWidget::sig_setBackground(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_skinWidget_t {
    QByteArrayData data[4];
    char stringdata0[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_skinWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_skinWidget_t qt_meta_stringdata_skinWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "skinWidget"
QT_MOC_LITERAL(1, 11, 19), // "slot_openPersonalBG"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 19) // "slot_setOpacityText"

    },
    "skinWidget\0slot_openPersonalBG\0\0"
    "slot_setOpacityText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_skinWidget[] = {

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
       1,    0,   24,    2, 0x0a /* Public */,
       3,    1,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void skinWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        skinWidget *_t = static_cast<skinWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_openPersonalBG(); break;
        case 1: _t->slot_setOpacityText((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject skinWidget::staticMetaObject = {
    { &baseDialog::staticMetaObject, qt_meta_stringdata_skinWidget.data,
      qt_meta_data_skinWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *skinWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *skinWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_skinWidget.stringdata0))
        return static_cast<void*>(const_cast< skinWidget*>(this));
    return baseDialog::qt_metacast(_clname);
}

int skinWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = baseDialog::qt_metacall(_c, _id, _a);
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
