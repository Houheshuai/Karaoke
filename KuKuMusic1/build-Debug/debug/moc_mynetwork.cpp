/****************************************************************************
** Meta object code from reading C++ file 'mynetwork.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../netWork/mynetwork.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mynetwork.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyNetWork_t {
    QByteArrayData data[20];
    char stringdata0[232];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyNetWork_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyNetWork_t qt_meta_stringdata_MyNetWork = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MyNetWork"
QT_MOC_LITERAL(1, 10, 17), // "sig_reqMvfinished"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 19), // "sig_reqSongFinished"
QT_MOC_LITERAL(4, 49, 27), // "sig_reqSongNextPagefinished"
QT_MOC_LITERAL(5, 77, 17), // "dolrcworkfinished"
QT_MOC_LITERAL(6, 95, 6), // "setpic"
QT_MOC_LITERAL(7, 102, 12), // "sig_setBgpix"
QT_MOC_LITERAL(8, 115, 16), // "QVector<QPixmap>"
QT_MOC_LITERAL(9, 132, 6), // "author"
QT_MOC_LITERAL(10, 139, 5), // "reqMv"
QT_MOC_LITERAL(11, 145, 8), // "reqAlbum"
QT_MOC_LITERAL(12, 154, 4), // "name"
QT_MOC_LITERAL(13, 159, 9), // "savelocal"
QT_MOC_LITERAL(14, 169, 7), // "reqSong"
QT_MOC_LITERAL(15, 177, 15), // "reqSongNextPage"
QT_MOC_LITERAL(16, 193, 6), // "reqLrc"
QT_MOC_LITERAL(17, 200, 9), // "totaltime"
QT_MOC_LITERAL(18, 210, 12), // "saveloaction"
QT_MOC_LITERAL(19, 223, 8) // "reqBgPic"

    },
    "MyNetWork\0sig_reqMvfinished\0\0"
    "sig_reqSongFinished\0sig_reqSongNextPagefinished\0"
    "dolrcworkfinished\0setpic\0sig_setBgpix\0"
    "QVector<QPixmap>\0author\0reqMv\0reqAlbum\0"
    "name\0savelocal\0reqSong\0reqSongNextPage\0"
    "reqLrc\0totaltime\0saveloaction\0reqBgPic"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyNetWork[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       3,    1,   77,    2, 0x06 /* Public */,
       4,    1,   80,    2, 0x06 /* Public */,
       5,    2,   83,    2, 0x06 /* Public */,
       6,    2,   88,    2, 0x06 /* Public */,
       7,    2,   93,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   98,    2, 0x0a /* Public */,
      11,    2,  101,    2, 0x0a /* Public */,
      14,    1,  106,    2, 0x0a /* Public */,
      15,    0,  109,    2, 0x0a /* Public */,
      16,    3,  110,    2, 0x0a /* Public */,
      19,    1,  117,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 8, QMetaType::QString,    2,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   12,   13,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong, QMetaType::QString,    2,   17,   18,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void MyNetWork::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyNetWork *_t = static_cast<MyNetWork *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_reqMvfinished((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->sig_reqSongFinished((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 2: _t->sig_reqSongNextPagefinished((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 3: _t->dolrcworkfinished((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->setpic((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->sig_setBgpix((*reinterpret_cast< const QVector<QPixmap>(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->reqMv((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->reqAlbum((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->reqSong((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->reqSongNextPage(); break;
        case 10: _t->reqLrc((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 11: _t->reqBgPic((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QPixmap> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MyNetWork::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyNetWork::sig_reqMvfinished)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MyNetWork::*_t)(const QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyNetWork::sig_reqSongFinished)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MyNetWork::*_t)(const QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyNetWork::sig_reqSongNextPagefinished)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MyNetWork::*_t)(const QByteArray & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyNetWork::dolrcworkfinished)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MyNetWork::*_t)(const QByteArray & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyNetWork::setpic)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MyNetWork::*_t)(const QVector<QPixmap> & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyNetWork::sig_setBgpix)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject MyNetWork::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MyNetWork.data,
      qt_meta_data_MyNetWork,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyNetWork::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyNetWork::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyNetWork.stringdata0))
        return static_cast<void*>(const_cast< MyNetWork*>(this));
    return QObject::qt_metacast(_clname);
}

int MyNetWork::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void MyNetWork::sig_reqMvfinished(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyNetWork::sig_reqSongFinished(const QByteArray & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyNetWork::sig_reqSongNextPagefinished(const QByteArray & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MyNetWork::dolrcworkfinished(const QByteArray & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MyNetWork::setpic(const QByteArray & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MyNetWork::sig_setBgpix(const QVector<QPixmap> & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
