/****************************************************************************
** Meta object code from reading C++ file 'ClientLogin.h'
**
** Created: Tue Jun 18 00:37:01 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ClientLogin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClientLogin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClientLogin[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   12,   12,   12, 0x0a,
      51,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ClientLogin[] = {
    "ClientLogin\0\0ReturnLoginSignal()\0"
    "sureBtn_clicked()\0"
    "ReadError(QAbstractSocket::SocketError)\0"
};

const QMetaObject ClientLogin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ClientLogin,
      qt_meta_data_ClientLogin, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClientLogin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClientLogin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClientLogin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClientLogin))
        return static_cast<void*>(const_cast< ClientLogin*>(this));
    return QWidget::qt_metacast(_clname);
}

int ClientLogin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ReturnLoginSignal(); break;
        case 1: sureBtn_clicked(); break;
        case 2: ReadError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ClientLogin::ReturnLoginSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
