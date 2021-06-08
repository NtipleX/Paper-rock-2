/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ClientProject/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_menuLabel_t {
    const uint offsetsAndSize[6];
    char stringdata0[26];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_menuLabel_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_menuLabel_t qt_meta_stringdata_menuLabel = {
    {
QT_MOC_LITERAL(0, 9), // "menuLabel"
QT_MOC_LITERAL(10, 14), // "myLabelClicked"
QT_MOC_LITERAL(25, 0) // ""

    },
    "menuLabel\0myLabelClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_menuLabel[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x06,    0 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void menuLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<menuLabel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->myLabelClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (menuLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&menuLabel::myLabelClicked)) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject menuLabel::staticMetaObject = { {
    QMetaObject::SuperData::link<QLabel::staticMetaObject>(),
    qt_meta_stringdata_menuLabel.offsetsAndSize,
    qt_meta_data_menuLabel,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_menuLabel_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *menuLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *menuLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_menuLabel.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int menuLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void menuLabel::myLabelClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[34];
    char stringdata0[287];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 15), // "on_bReg_clicked"
QT_MOC_LITERAL(27, 0), // ""
QT_MOC_LITERAL(28, 17), // "on_bLogin_clicked"
QT_MOC_LITERAL(46, 20), // "on_pl2_linkActivated"
QT_MOC_LITERAL(67, 4), // "link"
QT_MOC_LITERAL(72, 15), // "on_join_clicked"
QT_MOC_LITERAL(88, 17), // "on_join_2_clicked"
QT_MOC_LITERAL(106, 17), // "on_join_3_clicked"
QT_MOC_LITERAL(124, 17), // "on_join_4_clicked"
QT_MOC_LITERAL(142, 17), // "on_join_5_clicked"
QT_MOC_LITERAL(160, 21), // "on_signal_add_clicked"
QT_MOC_LITERAL(182, 13), // "on_pb_clicked"
QT_MOC_LITERAL(196, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(218, 20), // "on_closeChat_clicked"
QT_MOC_LITERAL(239, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(263, 23) // "on_pushButton_4_clicked"

    },
    "MainWindow\0on_bReg_clicked\0\0"
    "on_bLogin_clicked\0on_pl2_linkActivated\0"
    "link\0on_join_clicked\0on_join_2_clicked\0"
    "on_join_3_clicked\0on_join_4_clicked\0"
    "on_join_5_clicked\0on_signal_add_clicked\0"
    "on_pb_clicked\0on_pushButton_clicked\0"
    "on_closeChat_clicked\0on_pushButton_3_clicked\0"
    "on_pushButton_4_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   98,    2, 0x08,    0 /* Private */,
       3,    0,   99,    2, 0x08,    1 /* Private */,
       4,    1,  100,    2, 0x08,    2 /* Private */,
       6,    0,  103,    2, 0x08,    4 /* Private */,
       7,    0,  104,    2, 0x08,    5 /* Private */,
       8,    0,  105,    2, 0x08,    6 /* Private */,
       9,    0,  106,    2, 0x08,    7 /* Private */,
      10,    0,  107,    2, 0x08,    8 /* Private */,
      11,    0,  108,    2, 0x08,    9 /* Private */,
      12,    0,  109,    2, 0x08,   10 /* Private */,
      13,    0,  110,    2, 0x08,   11 /* Private */,
      14,    0,  111,    2, 0x08,   12 /* Private */,
      15,    0,  112,    2, 0x08,   13 /* Private */,
      16,    0,  113,    2, 0x08,   14 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_bReg_clicked(); break;
        case 1: _t->on_bLogin_clicked(); break;
        case 2: _t->on_pl2_linkActivated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_join_clicked(); break;
        case 4: _t->on_join_2_clicked(); break;
        case 5: _t->on_join_3_clicked(); break;
        case 6: _t->on_join_4_clicked(); break;
        case 7: _t->on_join_5_clicked(); break;
        case 8: _t->on_signal_add_clicked(); break;
        case 9: _t->on_pb_clicked(); break;
        case 10: _t->on_pushButton_clicked(); break;
        case 11: _t->on_closeChat_clicked(); break;
        case 12: _t->on_pushButton_3_clicked(); break;
        case 13: _t->on_pushButton_4_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
