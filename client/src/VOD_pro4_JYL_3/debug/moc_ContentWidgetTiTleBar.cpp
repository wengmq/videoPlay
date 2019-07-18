/****************************************************************************
** Meta object code from reading C++ file 'ContentWidgetTiTleBar.h'
**
** Created: Sat Jun 29 09:14:27 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../homepage/content/ContentWidgetTiTleBar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ContentWidgetTiTleBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ContentWidgetTiTleBar[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      33,   23,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
      55,   23,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ContentWidgetTiTleBar[] = {
    "ContentWidgetTiTleBar\0\0channelId\0"
    "channelBtnSignal(int)\0channelBtnSlot(int)\0"
};

const QMetaObject ContentWidgetTiTleBar::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ContentWidgetTiTleBar,
      qt_meta_data_ContentWidgetTiTleBar, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ContentWidgetTiTleBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ContentWidgetTiTleBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ContentWidgetTiTleBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ContentWidgetTiTleBar))
        return static_cast<void*>(const_cast< ContentWidgetTiTleBar*>(this));
    return QFrame::qt_metacast(_clname);
}

int ContentWidgetTiTleBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: channelBtnSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: channelBtnSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ContentWidgetTiTleBar::channelBtnSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
