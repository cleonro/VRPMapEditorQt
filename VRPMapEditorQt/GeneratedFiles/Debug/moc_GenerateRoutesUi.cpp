/****************************************************************************
** Meta object code from reading C++ file 'GenerateRoutesUi.h'
**
** Created: Wed Sep 7 00:48:22 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GenerateRoutesUi.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GenerateRoutesUi.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CVehicleCostUi[] = {

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
      16,   15,   15,   15, 0x09,
      34,   30,   15,   15, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CVehicleCostUi[] = {
    "CVehicleCostUi\0\0OnButtonMem()\0idx\0"
    "OnIndexChanged(int)\0"
};

const QMetaObject CVehicleCostUi::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CVehicleCostUi,
      qt_meta_data_CVehicleCostUi, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CVehicleCostUi::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CVehicleCostUi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CVehicleCostUi::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CVehicleCostUi))
        return static_cast<void*>(const_cast< CVehicleCostUi*>(this));
    return QDialog::qt_metacast(_clname);
}

int CVehicleCostUi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnButtonMem(); break;
        case 1: OnIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_CGenerateRoutesUi[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   18,   18,   18, 0x09,
      48,   18,   18,   18, 0x09,
      62,   18,   18,   18, 0x09,
      77,   18,   18,   18, 0x09,
      92,   18,   18,   18, 0x09,
     107,   18,   18,   18, 0x09,
     123,   18,   18,   18, 0x09,
     148,  131,   18,   18, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CGenerateRoutesUi[] = {
    "CGenerateRoutesUi\0\0showRead(bool)\0"
    "OnButtonOne()\0OnButtonAll()\0OnButtonInit()\0"
    "OnButtonCost()\0OnButtonSave()\0"
    "OnButtonReset()\0Clear()\0current,previous\0"
    "OnCurrentChanged(QModelIndex,QModelIndex)\0"
};

const QMetaObject CGenerateRoutesUi::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CGenerateRoutesUi,
      qt_meta_data_CGenerateRoutesUi, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CGenerateRoutesUi::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CGenerateRoutesUi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CGenerateRoutesUi::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CGenerateRoutesUi))
        return static_cast<void*>(const_cast< CGenerateRoutesUi*>(this));
    return QDialog::qt_metacast(_clname);
}

int CGenerateRoutesUi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showRead((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: OnButtonOne(); break;
        case 2: OnButtonAll(); break;
        case 3: OnButtonInit(); break;
        case 4: OnButtonCost(); break;
        case 5: OnButtonSave(); break;
        case 6: OnButtonReset(); break;
        case 7: Clear(); break;
        case 8: OnCurrentChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void CGenerateRoutesUi::showRead(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_CUiCustomRoutes[] = {

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
      17,   16,   16,   16, 0x09,
      36,   16,   16,   16, 0x09,
      51,   16,   16,   16, 0x09,
      59,   16,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CUiCustomRoutes[] = {
    "CUiCustomRoutes\0\0OnReadFileButton()\0"
    "OnSaveButton()\0Clear()\0ShowRead(bool)\0"
};

const QMetaObject CUiCustomRoutes::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CUiCustomRoutes,
      qt_meta_data_CUiCustomRoutes, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CUiCustomRoutes::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CUiCustomRoutes::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CUiCustomRoutes::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CUiCustomRoutes))
        return static_cast<void*>(const_cast< CUiCustomRoutes*>(this));
    return QDialog::qt_metacast(_clname);
}

int CUiCustomRoutes::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnReadFileButton(); break;
        case 1: OnSaveButton(); break;
        case 2: Clear(); break;
        case 3: ShowRead((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
