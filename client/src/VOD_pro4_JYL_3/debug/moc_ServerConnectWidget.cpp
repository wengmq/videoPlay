/****************************************************************************
** Meta object code from reading C++ file 'ServerConnectWidget.h'
**
** Created: Sat Jun 29 11:11:42 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ServerConnectWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ServerConnectWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ServerConnectWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,
      35,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ServerConnectWidget[] = {
    "ServerConnectWidget\0\0ConnectSlot()\0"
    "ChannelPacketReadSlot()\0"
};

const QMetaObject ServerConnectWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ServerConnectWidget,
      qt_meta_data_ServerConnectWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ServerConnectWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ServerConnectWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ServerConnectWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ServerConnectWidget))
        return static_cast<void*>(const_cast< ServerConnectWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ServerConnectWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ConnectSlot(); break;
        case 1: ChannelPacketReadSlot(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
