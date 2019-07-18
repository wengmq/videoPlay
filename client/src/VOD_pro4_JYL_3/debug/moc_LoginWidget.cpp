/****************************************************************************
** Meta object code from reading C++ file 'LoginWidget.h'
**
** Created: Sat Jun 29 09:14:23 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../homepage/LoginWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LoginWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LoginWidget[] = {

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
      23,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   12,   12,   12, 0x0a,
      60,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LoginWidget[] = {
    "LoginWidget\0\0loginFlag\0LoginSuccessSignal(bool)\0"
    "LoginSlot()\0PacketReadSlot()\0"
};

const QMetaObject LoginWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LoginWidget,
      qt_meta_data_LoginWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoginWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoginWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoginWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoginWidget))
        return static_cast<void*>(const_cast< LoginWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int LoginWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: LoginSuccessSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: LoginSlot(); break;
        case 2: PacketReadSlot(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void LoginWidget::LoginSuccessSignal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
