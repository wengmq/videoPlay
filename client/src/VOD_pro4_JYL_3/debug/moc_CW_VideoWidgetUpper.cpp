/****************************************************************************
** Meta object code from reading C++ file 'CW_VideoWidgetUpper.h'
**
** Created: Sat Jun 29 09:14:31 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../homepage/content/CW_VideoWidgetUpper.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CW_VideoWidgetUpper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CW_VideoWidgetUpper[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CW_VideoWidgetUpper[] = {
    "CW_VideoWidgetUpper\0\0onHoverAction()\0"
};

const QMetaObject CW_VideoWidgetUpper::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_CW_VideoWidgetUpper,
      qt_meta_data_CW_VideoWidgetUpper, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CW_VideoWidgetUpper::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CW_VideoWidgetUpper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CW_VideoWidgetUpper::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CW_VideoWidgetUpper))
        return static_cast<void*>(const_cast< CW_VideoWidgetUpper*>(this));
    return QFrame::qt_metacast(_clname);
}

int CW_VideoWidgetUpper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onHoverAction(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
