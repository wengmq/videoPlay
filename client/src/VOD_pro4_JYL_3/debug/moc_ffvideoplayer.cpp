/****************************************************************************
** Meta object code from reading C++ file 'ffvideoplayer.h'
**
** Created: Sat Jun 29 09:14:48 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../videoPlay/ffvideoplayer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ffvideoplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FFVideoPlayer[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      38,   14,   14,   14, 0x0a,
      68,   14,   14,   14, 0x0a,
      99,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FFVideoPlayer[] = {
    "FFVideoPlayer\0\0on_play_Btn_released()\0"
    "on_timeSlider_sliderPressed()\0"
    "on_timeSlider_sliderReleased()\0"
    "dialogCloseSlot()\0"
};

const QMetaObject FFVideoPlayer::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FFVideoPlayer,
      qt_meta_data_FFVideoPlayer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FFVideoPlayer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FFVideoPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FFVideoPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FFVideoPlayer))
        return static_cast<void*>(const_cast< FFVideoPlayer*>(this));
    return QDialog::qt_metacast(_clname);
}

int FFVideoPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_play_Btn_released(); break;
        case 1: on_timeSlider_sliderPressed(); break;
        case 2: on_timeSlider_sliderReleased(); break;
        case 3: dialogCloseSlot(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
