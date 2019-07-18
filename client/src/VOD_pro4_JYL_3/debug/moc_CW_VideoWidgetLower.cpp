/****************************************************************************
** Meta object code from reading C++ file 'CW_VideoWidgetLower.h'
**
** Created: Sat Jun 29 11:11:51 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../homepage/content/CW_VideoWidgetLower.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CW_VideoWidgetLower.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CW_VideoWidgetLower[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   21,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      62,   20,   20,   20, 0x0a,
      88,   20,   20,   20, 0x0a,
     113,  104,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CW_VideoWidgetLower[] = {
    "CW_VideoWidgetLower\0\0video_name\0"
    "videoPlaySignal(const char[])\0"
    "videoPlaySignalEmitSlot()\0videoPlaySlot()\0"
    "dataList\0setVideoData(QList<video_list_t>)\0"
};

const QMetaObject CW_VideoWidgetLower::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_CW_VideoWidgetLower,
      qt_meta_data_CW_VideoWidgetLower, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CW_VideoWidgetLower::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CW_VideoWidgetLower::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CW_VideoWidgetLower::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CW_VideoWidgetLower))
        return static_cast<void*>(const_cast< CW_VideoWidgetLower*>(this));
    return QFrame::qt_metacast(_clname);
}

int CW_VideoWidgetLower::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: videoPlaySignal((*reinterpret_cast< const char(*)[]>(_a[1]))); break;
        case 1: videoPlaySignalEmitSlot(); break;
        case 2: videoPlaySlot(); break;
        case 3: setVideoData((*reinterpret_cast< QList<video_list_t>(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CW_VideoWidgetLower::videoPlaySignal(const char _t1[])
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
