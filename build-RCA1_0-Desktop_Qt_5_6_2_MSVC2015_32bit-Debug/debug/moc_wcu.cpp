/****************************************************************************
** Meta object code from reading C++ file 'wcu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../connectors/wcu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wcu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Wcu_t {
    QByteArrayData data[7];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Wcu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Wcu_t qt_meta_stringdata_Wcu = {
    {
QT_MOC_LITERAL(0, 0, 3), // "Wcu"
QT_MOC_LITERAL(1, 4, 15), // "signalMsgFromCu"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 8), // "sockDisc"
QT_MOC_LITERAL(4, 30, 10), // "msgToCunit"
QT_MOC_LITERAL(5, 41, 3), // "msg"
QT_MOC_LITERAL(6, 45, 12) // "msgFromCunit"

    },
    "Wcu\0signalMsgFromCu\0\0sockDisc\0msgToCunit\0"
    "msg\0msgFromCunit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Wcu[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   37,    2, 0x0a /* Public */,
       4,    1,   38,    2, 0x0a /* Public */,
       6,    0,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void,

       0        // eod
};

void Wcu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Wcu *_t = static_cast<Wcu *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalMsgFromCu((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->sockDisc(); break;
        case 2: _t->msgToCunit((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->msgFromCunit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Wcu::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Wcu::signalMsgFromCu)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Wcu::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_Wcu.data,
      qt_meta_data_Wcu,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Wcu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Wcu::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Wcu.stringdata0))
        return static_cast<void*>(const_cast< Wcu*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int Wcu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Wcu::signalMsgFromCu(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
