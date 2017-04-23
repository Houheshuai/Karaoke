/****************************************************************************
** Meta object code from reading C++ file 'mytablewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tableWidgetFiles/mytablewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mytablewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_myTableWidget_t {
    QByteArrayData data[27];
    char stringdata0[409];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myTableWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myTableWidget_t qt_meta_stringdata_myTableWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "myTableWidget"
QT_MOC_LITERAL(1, 14, 13), // "sig_requestMv"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 16), // "sig_setLoveState"
QT_MOC_LITERAL(4, 46, 10), // "sig_playMv"
QT_MOC_LITERAL(5, 57, 8), // "sig_play"
QT_MOC_LITERAL(6, 66, 12), // "sig_delIndex"
QT_MOC_LITERAL(7, 79, 17), // "sig_addSongFolder"
QT_MOC_LITERAL(8, 97, 11), // "sig_addSong"
QT_MOC_LITERAL(9, 109, 18), // "sig_RowCountChange"
QT_MOC_LITERAL(10, 128, 14), // "slot_mvclicked"
QT_MOC_LITERAL(11, 143, 32), // "slot_playingWidgetLoveBtnClicked"
QT_MOC_LITERAL(12, 176, 19), // "slot_btnloveclicked"
QT_MOC_LITERAL(13, 196, 20), // "slot_rowCountChanged"
QT_MOC_LITERAL(14, 217, 12), // "slot_actplay"
QT_MOC_LITERAL(15, 230, 16), // "slot_cellClicked"
QT_MOC_LITERAL(16, 247, 19), // "slot_removeHoverRow"
QT_MOC_LITERAL(17, 267, 14), // "slot_removeRow"
QT_MOC_LITERAL(18, 282, 14), // "slot_cellEnter"
QT_MOC_LITERAL(19, 297, 14), // "slot_animation"
QT_MOC_LITERAL(20, 312, 9), // "QVariant&"
QT_MOC_LITERAL(21, 322, 13), // "slot_doublick"
QT_MOC_LITERAL(22, 336, 1), // "r"
QT_MOC_LITERAL(23, 338, 4), // "isMv"
QT_MOC_LITERAL(24, 343, 16), // "slot_menuRequest"
QT_MOC_LITERAL(25, 360, 16), // "slot_moveToPList"
QT_MOC_LITERAL(26, 377, 31) // "slot_playingWidgetDelBtnClicked"

    },
    "myTableWidget\0sig_requestMv\0\0"
    "sig_setLoveState\0sig_playMv\0sig_play\0"
    "sig_delIndex\0sig_addSongFolder\0"
    "sig_addSong\0sig_RowCountChange\0"
    "slot_mvclicked\0slot_playingWidgetLoveBtnClicked\0"
    "slot_btnloveclicked\0slot_rowCountChanged\0"
    "slot_actplay\0slot_cellClicked\0"
    "slot_removeHoverRow\0slot_removeRow\0"
    "slot_cellEnter\0slot_animation\0QVariant&\0"
    "slot_doublick\0r\0isMv\0slot_menuRequest\0"
    "slot_moveToPList\0slot_playingWidgetDelBtnClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myTableWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  129,    2, 0x06 /* Public */,
       3,    1,  132,    2, 0x06 /* Public */,
       4,    1,  135,    2, 0x06 /* Public */,
       5,    1,  138,    2, 0x06 /* Public */,
       6,    1,  141,    2, 0x06 /* Public */,
       7,    0,  144,    2, 0x06 /* Public */,
       8,    0,  145,    2, 0x06 /* Public */,
       9,    0,  146,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,  147,    2, 0x0a /* Public */,
      11,    0,  148,    2, 0x0a /* Public */,
      12,    0,  149,    2, 0x0a /* Public */,
      13,    0,  150,    2, 0x0a /* Public */,
      14,    0,  151,    2, 0x0a /* Public */,
      15,    2,  152,    2, 0x0a /* Public */,
      16,    0,  157,    2, 0x0a /* Public */,
      17,    0,  158,    2, 0x0a /* Public */,
      18,    2,  159,    2, 0x0a /* Public */,
      19,    1,  164,    2, 0x0a /* Public */,
      21,    3,  167,    2, 0x0a /* Public */,
      21,    2,  174,    2, 0x2a /* Public | MethodCloned */,
      24,    1,  179,    2, 0x0a /* Public */,
      25,    0,  182,    2, 0x0a /* Public */,
      26,    0,  183,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 20,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Bool,   22,    2,   23,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   22,    2,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void myTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myTableWidget *_t = static_cast<myTableWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_requestMv((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sig_setLoveState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->sig_playMv((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->sig_play((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->sig_delIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sig_addSongFolder(); break;
        case 6: _t->sig_addSong(); break;
        case 7: _t->sig_RowCountChange(); break;
        case 8: _t->slot_mvclicked(); break;
        case 9: _t->slot_playingWidgetLoveBtnClicked(); break;
        case 10: _t->slot_btnloveclicked(); break;
        case 11: _t->slot_rowCountChanged(); break;
        case 12: _t->slot_actplay(); break;
        case 13: _t->slot_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->slot_removeHoverRow(); break;
        case 15: _t->slot_removeRow(); break;
        case 16: _t->slot_cellEnter((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 17: _t->slot_animation((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 18: _t->slot_doublick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 19: _t->slot_doublick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 20: _t->slot_menuRequest((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 21: _t->slot_moveToPList(); break;
        case 22: _t->slot_playingWidgetDelBtnClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (myTableWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myTableWidget::sig_requestMv)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (myTableWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myTableWidget::sig_setLoveState)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (myTableWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myTableWidget::sig_playMv)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (myTableWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myTableWidget::sig_play)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (myTableWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myTableWidget::sig_delIndex)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (myTableWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myTableWidget::sig_addSongFolder)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (myTableWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myTableWidget::sig_addSong)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (myTableWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myTableWidget::sig_RowCountChange)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject myTableWidget::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_myTableWidget.data,
      qt_meta_data_myTableWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *myTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_myTableWidget.stringdata0))
        return static_cast<void*>(const_cast< myTableWidget*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int myTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void myTableWidget::sig_requestMv(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void myTableWidget::sig_setLoveState(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void myTableWidget::sig_playMv(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void myTableWidget::sig_play(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void myTableWidget::sig_delIndex(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void myTableWidget::sig_addSongFolder()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void myTableWidget::sig_addSong()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void myTableWidget::sig_RowCountChange()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
