/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainWindows/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_mainWindow_t {
    QByteArrayData data[24];
    char stringdata0[429];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mainWindow_t qt_meta_stringdata_mainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "mainWindow"
QT_MOC_LITERAL(1, 11, 13), // "sig_requestMv"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 16), // "sig_requestBgPic"
QT_MOC_LITERAL(4, 43, 14), // "sig_requestLrc"
QT_MOC_LITERAL(5, 58, 16), // "sig_requestAlbum"
QT_MOC_LITERAL(6, 75, 22), // "slot_currentMediaError"
QT_MOC_LITERAL(7, 98, 25), // "slot_setPlayerPlayOrPause"
QT_MOC_LITERAL(8, 124, 19), // "slot_OpenDeskTopLrc"
QT_MOC_LITERAL(9, 144, 22), // "slot_timelineAnimation"
QT_MOC_LITERAL(10, 167, 13), // "slot_setBgPix"
QT_MOC_LITERAL(11, 181, 16), // "QVector<QPixmap>"
QT_MOC_LITERAL(12, 198, 12), // "slot_quitApp"
QT_MOC_LITERAL(13, 211, 16), // "slot_setPlayMode"
QT_MOC_LITERAL(14, 228, 8), // "PlayMode"
QT_MOC_LITERAL(15, 237, 22), // "slot_setPlayModeWidget"
QT_MOC_LITERAL(16, 260, 24), // "slot_currentMediaChanged"
QT_MOC_LITERAL(17, 285, 4), // "isMV"
QT_MOC_LITERAL(18, 290, 18), // "slot_iconIsActived"
QT_MOC_LITERAL(19, 309, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(20, 343, 19), // "slot_positionChange"
QT_MOC_LITERAL(21, 363, 24), // "slot_playerStatusChanged"
QT_MOC_LITERAL(22, 388, 12), // "PlayerStatus"
QT_MOC_LITERAL(23, 401, 27) // "slot_adjustWindowNormalSize"

    },
    "mainWindow\0sig_requestMv\0\0sig_requestBgPic\0"
    "sig_requestLrc\0sig_requestAlbum\0"
    "slot_currentMediaError\0slot_setPlayerPlayOrPause\0"
    "slot_OpenDeskTopLrc\0slot_timelineAnimation\0"
    "slot_setBgPix\0QVector<QPixmap>\0"
    "slot_quitApp\0slot_setPlayMode\0PlayMode\0"
    "slot_setPlayModeWidget\0slot_currentMediaChanged\0"
    "isMV\0slot_iconIsActived\0"
    "QSystemTrayIcon::ActivationReason\0"
    "slot_positionChange\0slot_playerStatusChanged\0"
    "PlayerStatus\0slot_adjustWindowNormalSize"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       3,    1,  102,    2, 0x06 /* Public */,
       4,    3,  105,    2, 0x06 /* Public */,
       5,    2,  112,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  117,    2, 0x0a /* Public */,
       7,    0,  118,    2, 0x0a /* Public */,
       8,    0,  119,    2, 0x0a /* Public */,
       9,    1,  120,    2, 0x0a /* Public */,
      10,    2,  123,    2, 0x0a /* Public */,
      12,    0,  128,    2, 0x0a /* Public */,
      13,    1,  129,    2, 0x0a /* Public */,
      15,    0,  132,    2, 0x0a /* Public */,
      16,    2,  133,    2, 0x0a /* Public */,
      18,    1,  138,    2, 0x0a /* Public */,
      20,    1,  141,    2, 0x0a /* Public */,
      21,    1,  144,    2, 0x0a /* Public */,
      23,    0,  147,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong, QMetaType::QString,    2,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 11, QMetaType::QString,    2,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    2,   17,
    QMetaType::Void, 0x80000000 | 19,    2,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void, 0x80000000 | 22,    2,
    QMetaType::Void,

       0        // eod
};

void mainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mainWindow *_t = static_cast<mainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_requestMv((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->sig_requestBgPic((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->sig_requestLrc((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 3: _t->sig_requestAlbum((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->slot_currentMediaError(); break;
        case 5: _t->slot_setPlayerPlayOrPause(); break;
        case 6: _t->slot_OpenDeskTopLrc(); break;
        case 7: _t->slot_timelineAnimation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->slot_setBgPix((*reinterpret_cast< const QVector<QPixmap>(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->slot_quitApp(); break;
        case 10: _t->slot_setPlayMode((*reinterpret_cast< PlayMode(*)>(_a[1]))); break;
        case 11: _t->slot_setPlayModeWidget(); break;
        case 12: _t->slot_currentMediaChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 13: _t->slot_iconIsActived((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 14: _t->slot_positionChange((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 15: _t->slot_playerStatusChanged((*reinterpret_cast< PlayerStatus(*)>(_a[1]))); break;
        case 16: _t->slot_adjustWindowNormalSize(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
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
            typedef void (mainWindow::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainWindow::sig_requestMv)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (mainWindow::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainWindow::sig_requestBgPic)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (mainWindow::*_t)(const QString & , qint64 , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainWindow::sig_requestLrc)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (mainWindow::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainWindow::sig_requestAlbum)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject mainWindow::staticMetaObject = {
    { &baseWindow::staticMetaObject, qt_meta_stringdata_mainWindow.data,
      qt_meta_data_mainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *mainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_mainWindow.stringdata0))
        return static_cast<void*>(const_cast< mainWindow*>(this));
    return baseWindow::qt_metacast(_clname);
}

int mainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = baseWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void mainWindow::sig_requestMv(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void mainWindow::sig_requestBgPic(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void mainWindow::sig_requestLrc(const QString & _t1, qint64 _t2, const QString & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void mainWindow::sig_requestAlbum(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
