/****************************************************************************
** Meta object code from reading C++ file 'FriendtrackerUI.hpp'
**
** Created: Mon Mar 25 21:13:40 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/FriendtrackerUI.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FriendtrackerUI.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FriendtrackerUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       1,   99, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      48,   42,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      80,   16,   16,   16, 0x0a,
      94,   16,   16,   16, 0x0a,
     112,   16,   16,   16, 0x0a,
     134,   16,   16,   16, 0x0a,
     165,   16,   16,   16, 0x0a,
     188,   16,   16,   16, 0x0a,
     217,   16,  205,   16, 0x0a,
     231,   42,   16,   16, 0x0a,
     259,   16,   16,   16, 0x0a,
     275,   16,   16,   16, 0x0a,

 // methods: signature, parameters, type, tag, flags
     320,  310,   16,   16, 0x02,
     343,   16,   16,   16, 0x02,
     361,   16,   16,   16, 0x02,
     391,  389,  381,   16, 0x02,
     420,  389,   16,   16, 0x02,

 // properties: name, type, flags
     450,  205, 0x0b495103,

 // properties: notify_signal_id
       1,

       0        // eod
};

static const char qt_meta_stringdata_FriendtrackerUI[] = {
    "FriendtrackerUI\0\0userProfileInitialized()\0"
    "ppIds\0onlinePpIdsChanged(QStringList)\0"
    "initWebMaps()\0initUserProfile()\0"
    "login(QGeoCoordinate)\0"
    "updateLocation(QGeoCoordinate)\0"
    "setSessionKey(QString)\0endApplication()\0"
    "QStringList\0onlinePpIds()\0"
    "setOnlinePpIds(QStringList)\0pullLocations()\0"
    "updateFriendsLocation(QList<User>)\0"
    "frequency\0setRegularMode(double)\0"
    "setRealtimeMode()\0setVisibility(bool)\0"
    "QString\0,\0getValueFor(QString,QString)\0"
    "saveValueFor(QString,QString)\0onlinePpIds\0"
};

void FriendtrackerUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FriendtrackerUI *_t = static_cast<FriendtrackerUI *>(_o);
        switch (_id) {
        case 0: _t->userProfileInitialized(); break;
        case 1: _t->onlinePpIdsChanged((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 2: _t->initWebMaps(); break;
        case 3: _t->initUserProfile(); break;
        case 4: _t->login((*reinterpret_cast< const QGeoCoordinate(*)>(_a[1]))); break;
        case 5: _t->updateLocation((*reinterpret_cast< const QGeoCoordinate(*)>(_a[1]))); break;
        case 6: _t->setSessionKey((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->endApplication(); break;
        case 8: { QStringList _r = _t->onlinePpIds();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 9: _t->setOnlinePpIds((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 10: _t->pullLocations(); break;
        case 11: _t->updateFriendsLocation((*reinterpret_cast< const QList<User>(*)>(_a[1]))); break;
        case 12: _t->setRegularMode((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->setRealtimeMode(); break;
        case 14: _t->setVisibility((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: { QString _r = _t->getValueFor((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 16: _t->saveValueFor((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FriendtrackerUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FriendtrackerUI::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FriendtrackerUI,
      qt_meta_data_FriendtrackerUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FriendtrackerUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FriendtrackerUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FriendtrackerUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FriendtrackerUI))
        return static_cast<void*>(const_cast< FriendtrackerUI*>(this));
    return QObject::qt_metacast(_clname);
}

int FriendtrackerUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QStringList*>(_v) = onlinePpIds(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setOnlinePpIds(*reinterpret_cast< QStringList*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void FriendtrackerUI::userProfileInitialized()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void FriendtrackerUI::onlinePpIdsChanged(const QStringList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
