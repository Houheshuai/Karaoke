/****************************************************************************
** Meta object code from reading C++ file 'lyriclabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../middleWidget/lyriclabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lyriclabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AbstractWheelWidget_t {
    QByteArrayData data[6];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AbstractWheelWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AbstractWheelWidget_t qt_meta_stringdata_AbstractWheelWidget = {
    {
QT_MOC_LITERAL(0, 0, 19), // "AbstractWheelWidget"
QT_MOC_LITERAL(1, 20, 7), // "stopped"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 5), // "index"
QT_MOC_LITERAL(4, 35, 8), // "changeTo"
QT_MOC_LITERAL(5, 44, 8) // "scrollTo"

    },
    "AbstractWheelWidget\0stopped\0\0index\0"
    "changeTo\0scrollTo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AbstractWheelWidget[] = {

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
       4,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void AbstractWheelWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AbstractWheelWidget *_t = static_cast<AbstractWheelWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stopped((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->changeTo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->scrollTo((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AbstractWheelWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbstractWheelWidget::stopped)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AbstractWheelWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbstractWheelWidget::changeTo)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject AbstractWheelWidget::staticMetaObject = {
    { &baseWidget::staticMetaObject, qt_meta_stringdata_AbstractWheelWidget.data,
      qt_meta_data_AbstractWheelWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AbstractWheelWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AbstractWheelWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AbstractWheelWidget.stringdata0))
        return static_cast<void*>(const_cast< AbstractWheelWidget*>(this));
    return baseWidget::qt_metacast(_clname);
}

int AbstractWheelWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = baseWidget::qt_metacall(_c, _id, _a);
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
void AbstractWheelWidget::stopped(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AbstractWheelWidget::changeTo(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_LyricLabel_t {
    QByteArrayData data[29];
    char stringdata0[382];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LyricLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LyricLabel_t qt_meta_stringdata_LyricLabel = {
    {
QT_MOC_LITERAL(0, 0, 10), // "LyricLabel"
QT_MOC_LITERAL(1, 11, 16), // "changeToPosition"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 3), // "pos"
QT_MOC_LITERAL(4, 33, 12), // "rightClicked"
QT_MOC_LITERAL(5, 46, 10), // "mouseEnter"
QT_MOC_LITERAL(6, 57, 20), // "sig_currentLrcChange"
QT_MOC_LITERAL(7, 78, 24), // "sig_currentPrecentChange"
QT_MOC_LITERAL(8, 103, 6), // "float&"
QT_MOC_LITERAL(9, 110, 7), // "precent"
QT_MOC_LITERAL(10, 118, 4), // "int&"
QT_MOC_LITERAL(11, 123, 8), // "interval"
QT_MOC_LITERAL(12, 132, 14), // "slot_timerWork"
QT_MOC_LITERAL(13, 147, 21), // "slot_openLocalLrcFile"
QT_MOC_LITERAL(14, 169, 20), // "setForwardHalfSecond"
QT_MOC_LITERAL(15, 190, 17), // "setBackHalfSecond"
QT_MOC_LITERAL(16, 208, 20), // "setForwardTwoSeconds"
QT_MOC_LITERAL(17, 229, 17), // "setBackTwoSeconds"
QT_MOC_LITERAL(18, 247, 20), // "setSingerBGShowOrNot"
QT_MOC_LITERAL(19, 268, 15), // "positionChanged"
QT_MOC_LITERAL(20, 284, 6), // "length"
QT_MOC_LITERAL(21, 291, 10), // "setPostion"
QT_MOC_LITERAL(22, 302, 13), // "slot_replyLrc"
QT_MOC_LITERAL(23, 316, 3), // "byt"
QT_MOC_LITERAL(24, 320, 8), // "songname"
QT_MOC_LITERAL(25, 329, 13), // "changeToEvent"
QT_MOC_LITERAL(26, 343, 5), // "index"
QT_MOC_LITERAL(27, 349, 10), // "changeFont"
QT_MOC_LITERAL(28, 360, 21) // "changeHightLightColor"

    },
    "LyricLabel\0changeToPosition\0\0pos\0"
    "rightClicked\0mouseEnter\0sig_currentLrcChange\0"
    "sig_currentPrecentChange\0float&\0precent\0"
    "int&\0interval\0slot_timerWork\0"
    "slot_openLocalLrcFile\0setForwardHalfSecond\0"
    "setBackHalfSecond\0setForwardTwoSeconds\0"
    "setBackTwoSeconds\0setSingerBGShowOrNot\0"
    "positionChanged\0length\0setPostion\0"
    "slot_replyLrc\0byt\0songname\0changeToEvent\0"
    "index\0changeFont\0changeHightLightColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LyricLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x06 /* Public */,
       4,    0,  107,    2, 0x06 /* Public */,
       5,    0,  108,    2, 0x06 /* Public */,
       6,    2,  109,    2, 0x06 /* Public */,
       7,    3,  114,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,  121,    2, 0x0a /* Public */,
      13,    0,  122,    2, 0x0a /* Public */,
      14,    0,  123,    2, 0x0a /* Public */,
      15,    0,  124,    2, 0x0a /* Public */,
      16,    0,  125,    2, 0x0a /* Public */,
      17,    0,  126,    2, 0x0a /* Public */,
      18,    0,  127,    2, 0x0a /* Public */,
      19,    1,  128,    2, 0x0a /* Public */,
      21,    1,  131,    2, 0x0a /* Public */,
      22,    2,  134,    2, 0x0a /* Public */,
      25,    1,  139,    2, 0x09 /* Protected */,
      27,    0,  142,    2, 0x09 /* Protected */,
      28,    0,  143,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 8, 0x80000000 | 10,    2,    9,   11,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   20,
    QMetaType::Void, QMetaType::LongLong,    3,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QString,   23,   24,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LyricLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LyricLabel *_t = static_cast<LyricLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeToPosition((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 1: _t->rightClicked(); break;
        case 2: _t->mouseEnter(); break;
        case 3: _t->sig_currentLrcChange((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->sig_currentPrecentChange((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->slot_timerWork(); break;
        case 6: _t->slot_openLocalLrcFile(); break;
        case 7: _t->setForwardHalfSecond(); break;
        case 8: _t->setBackHalfSecond(); break;
        case 9: _t->setForwardTwoSeconds(); break;
        case 10: _t->setBackTwoSeconds(); break;
        case 11: _t->setSingerBGShowOrNot(); break;
        case 12: _t->positionChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 13: _t->setPostion((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 14: _t->slot_replyLrc((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 15: _t->changeToEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->changeFont(); break;
        case 17: _t->changeHightLightColor(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LyricLabel::*_t)(qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LyricLabel::changeToPosition)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (LyricLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LyricLabel::rightClicked)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (LyricLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LyricLabel::mouseEnter)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (LyricLabel::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LyricLabel::sig_currentLrcChange)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (LyricLabel::*_t)(const QString & , float & , int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LyricLabel::sig_currentPrecentChange)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject LyricLabel::staticMetaObject = {
    { &AbstractWheelWidget::staticMetaObject, qt_meta_stringdata_LyricLabel.data,
      qt_meta_data_LyricLabel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LyricLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LyricLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LyricLabel.stringdata0))
        return static_cast<void*>(const_cast< LyricLabel*>(this));
    return AbstractWheelWidget::qt_metacast(_clname);
}

int LyricLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractWheelWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void LyricLabel::changeToPosition(qint64 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LyricLabel::rightClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void LyricLabel::mouseEnter()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void LyricLabel::sig_currentLrcChange(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void LyricLabel::sig_currentPrecentChange(const QString & _t1, float & _t2, int & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
