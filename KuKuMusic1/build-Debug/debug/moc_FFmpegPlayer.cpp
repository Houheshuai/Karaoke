/****************************************************************************
** Meta object code from reading C++ file 'FFmpegPlayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PlayCore/FFmpegPlayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FFmpegPlayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FFmpegPlayer_t {
    QByteArrayData data[16];
    char stringdata0[246];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FFmpegPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FFmpegPlayer_t qt_meta_stringdata_FFmpegPlayer = {
    {
QT_MOC_LITERAL(0, 0, 12), // "FFmpegPlayer"
QT_MOC_LITERAL(1, 13, 20), // "sig_BufferingPrecent"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 18), // "sig_CurImageChange"
QT_MOC_LITERAL(4, 54, 22), // "sig_CurrentMediaChange"
QT_MOC_LITERAL(5, 77, 4), // "isMv"
QT_MOC_LITERAL(6, 82, 30), // "sig_CurrentMediaDurationChange"
QT_MOC_LITERAL(7, 113, 18), // "sig_PositionChange"
QT_MOC_LITERAL(8, 132, 24), // "sig_CurrentMediaFinished"
QT_MOC_LITERAL(9, 157, 22), // "sig_CurrentMediaStatus"
QT_MOC_LITERAL(10, 180, 12), // "PlayerStatus"
QT_MOC_LITERAL(11, 193, 21), // "sig_CurrentMediaError"
QT_MOC_LITERAL(12, 215, 14), // "slot_timerWork"
QT_MOC_LITERAL(13, 230, 6), // "setVol"
QT_MOC_LITERAL(14, 237, 3), // "vol"
QT_MOC_LITERAL(15, 241, 4) // "seek"

    },
    "FFmpegPlayer\0sig_BufferingPrecent\0\0"
    "sig_CurImageChange\0sig_CurrentMediaChange\0"
    "isMv\0sig_CurrentMediaDurationChange\0"
    "sig_PositionChange\0sig_CurrentMediaFinished\0"
    "sig_CurrentMediaStatus\0PlayerStatus\0"
    "sig_CurrentMediaError\0slot_timerWork\0"
    "setVol\0vol\0seek"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FFmpegPlayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       3,    1,   72,    2, 0x06 /* Public */,
       4,    2,   75,    2, 0x06 /* Public */,
       6,    1,   80,    2, 0x06 /* Public */,
       7,    1,   83,    2, 0x06 /* Public */,
       8,    0,   86,    2, 0x06 /* Public */,
       9,    1,   87,    2, 0x06 /* Public */,
      11,    0,   90,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   91,    2, 0x0a /* Public */,
      13,    1,   92,    2, 0x0a /* Public */,
      15,    1,   95,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    2,    5,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::LongLong,    2,

       0        // eod
};

void FFmpegPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FFmpegPlayer *_t = static_cast<FFmpegPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_BufferingPrecent((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->sig_CurImageChange((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 2: _t->sig_CurrentMediaChange((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->sig_CurrentMediaDurationChange((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 4: _t->sig_PositionChange((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 5: _t->sig_CurrentMediaFinished(); break;
        case 6: _t->sig_CurrentMediaStatus((*reinterpret_cast< PlayerStatus(*)>(_a[1]))); break;
        case 7: _t->sig_CurrentMediaError(); break;
        case 8: _t->slot_timerWork(); break;
        case 9: _t->setVol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->seek((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FFmpegPlayer::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FFmpegPlayer::sig_BufferingPrecent)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (FFmpegPlayer::*_t)(QImage );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FFmpegPlayer::sig_CurImageChange)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (FFmpegPlayer::*_t)(const QString & , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FFmpegPlayer::sig_CurrentMediaChange)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (FFmpegPlayer::*_t)(qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FFmpegPlayer::sig_CurrentMediaDurationChange)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (FFmpegPlayer::*_t)(qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FFmpegPlayer::sig_PositionChange)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (FFmpegPlayer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FFmpegPlayer::sig_CurrentMediaFinished)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (FFmpegPlayer::*_t)(PlayerStatus );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FFmpegPlayer::sig_CurrentMediaStatus)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (FFmpegPlayer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FFmpegPlayer::sig_CurrentMediaError)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject FFmpegPlayer::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_FFmpegPlayer.data,
      qt_meta_data_FFmpegPlayer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FFmpegPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FFmpegPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FFmpegPlayer.stringdata0))
        return static_cast<void*>(const_cast< FFmpegPlayer*>(this));
    return QThread::qt_metacast(_clname);
}

int FFmpegPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void FFmpegPlayer::sig_BufferingPrecent(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FFmpegPlayer::sig_CurImageChange(QImage _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FFmpegPlayer::sig_CurrentMediaChange(const QString & _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FFmpegPlayer::sig_CurrentMediaDurationChange(qint64 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FFmpegPlayer::sig_PositionChange(qint64 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void FFmpegPlayer::sig_CurrentMediaFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void FFmpegPlayer::sig_CurrentMediaStatus(PlayerStatus _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void FFmpegPlayer::sig_CurrentMediaError()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
