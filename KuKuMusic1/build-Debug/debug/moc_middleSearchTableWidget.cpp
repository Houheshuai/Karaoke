/****************************************************************************
** Meta object code from reading C++ file 'middleSearchTableWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../middleWidget/middleSearchTableWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'middleSearchTableWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tableCellWidget_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tableCellWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tableCellWidget_t qt_meta_stringdata_tableCellWidget = {
    {
QT_MOC_LITERAL(0, 0, 15) // "tableCellWidget"

    },
    "tableCellWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tableCellWidget[] = {

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

void tableCellWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject tableCellWidget::staticMetaObject = {
    { &baseWidget::staticMetaObject, qt_meta_stringdata_tableCellWidget.data,
      qt_meta_data_tableCellWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *tableCellWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tableCellWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_tableCellWidget.stringdata0))
        return static_cast<void*>(const_cast< tableCellWidget*>(this));
    return baseWidget::qt_metacast(_clname);
}

int tableCellWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = baseWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_middleSearchTableWidget_t {
    QByteArrayData data[13];
    char stringdata0[209];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_middleSearchTableWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_middleSearchTableWidget_t qt_meta_stringdata_middleSearchTableWidget = {
    {
QT_MOC_LITERAL(0, 0, 23), // "middleSearchTableWidget"
QT_MOC_LITERAL(1, 24, 17), // "sig_doubleclicked"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 29), // "slot_tableContainerBtnClicked"
QT_MOC_LITERAL(4, 73, 19), // "slot_playbtnclicked"
QT_MOC_LITERAL(5, 93, 18), // "slot_addbtnclicked"
QT_MOC_LITERAL(6, 112, 23), // "slot_downloadbtnclicked"
QT_MOC_LITERAL(7, 136, 14), // "slot_cellEnter"
QT_MOC_LITERAL(8, 151, 3), // "row"
QT_MOC_LITERAL(9, 155, 1), // "c"
QT_MOC_LITERAL(10, 157, 14), // "slot_itemclick"
QT_MOC_LITERAL(11, 172, 18), // "slot_doubleClicked"
QT_MOC_LITERAL(12, 191, 17) // "QTableWidgetItem*"

    },
    "middleSearchTableWidget\0sig_doubleclicked\0"
    "\0slot_tableContainerBtnClicked\0"
    "slot_playbtnclicked\0slot_addbtnclicked\0"
    "slot_downloadbtnclicked\0slot_cellEnter\0"
    "row\0c\0slot_itemclick\0slot_doubleClicked\0"
    "QTableWidgetItem*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_middleSearchTableWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   61,    2, 0x0a /* Public */,
       4,    0,   62,    2, 0x0a /* Public */,
       5,    0,   63,    2, 0x0a /* Public */,
       6,    0,   64,    2, 0x0a /* Public */,
       7,    2,   65,    2, 0x0a /* Public */,
      10,    2,   70,    2, 0x0a /* Public */,
      11,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList, QMetaType::QStringList, QMetaType::QStringList,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 12,    2,

       0        // eod
};

void middleSearchTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        middleSearchTableWidget *_t = static_cast<middleSearchTableWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_doubleclicked((*reinterpret_cast< const QStringList(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2])),(*reinterpret_cast< const QStringList(*)>(_a[3]))); break;
        case 1: _t->slot_tableContainerBtnClicked(); break;
        case 2: _t->slot_playbtnclicked(); break;
        case 3: _t->slot_addbtnclicked(); break;
        case 4: _t->slot_downloadbtnclicked(); break;
        case 5: _t->slot_cellEnter((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->slot_itemclick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->slot_doubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (middleSearchTableWidget::*_t)(const QStringList & , const QStringList & , const QStringList & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&middleSearchTableWidget::sig_doubleclicked)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject middleSearchTableWidget::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_middleSearchTableWidget.data,
      qt_meta_data_middleSearchTableWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *middleSearchTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *middleSearchTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_middleSearchTableWidget.stringdata0))
        return static_cast<void*>(const_cast< middleSearchTableWidget*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int middleSearchTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void middleSearchTableWidget::sig_doubleclicked(const QStringList & _t1, const QStringList & _t2, const QStringList & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
