/****************************************************************************
** Meta object code from reading C++ file 'WebMaps.hpp'
**
** Created: Thu Mar 28 22:54:18 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/WebMaps.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WebMaps.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WebMaps[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       6,   79, // properties
       1,  103, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      34,    8,    8,    8, 0x05,
      58,   52,    8,    8, 0x05,
      88,   52,    8,    8, 0x05,
     122,    8,    8,    8, 0x05,
     134,    8,    8,    8, 0x05,
     168,  148,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
     217,    8,    8,    8, 0x0a,
     232,    8,    8,    8, 0x0a,
     261,  256,    8,    8, 0x0a,
     302,    8,    8,    8, 0x0a,
     316,    8,    8,    8, 0x0a,

 // methods: signature, parameters, type, tag, flags
     339,  333,    8,    8, 0x02,

 // properties: name, type, flags
     378,  369, 0x0049510b,
     402,  394, 0x0a495001,
     414,  394, 0x0a495001,
     428,  394, 0x0a495001,
     444,  437, 0x06095001,
     450,  437, 0x06095001,

 // properties: notify_signal_id
       0,
       0,
       1,
       1,
       0,
       0,

 // enums: name, flags, count, data
     369, 0x0,    3,  107,

 // enum data: key, value
     456, uint(WebMaps::GoogleMaps),
     467, uint(WebMaps::BingMaps),
     476, uint(WebMaps::OpenLayers),

       0        // eod
};

static const char qt_meta_stringdata_WebMaps[] = {
    "WebMaps\0\0currentProviderChanged()\0"
    "viewModeChanged()\0coord\0"
    "gotMyLocation(QGeoCoordinate)\0"
    "myLocationChanged(QGeoCoordinate)\0"
    "subscribe()\0unsubscribe()\0ppId,x,y,visibility\0"
    "friendLocationChanged(QString,double,double,int)\0"
    "nextViewMode()\0positionUpdateTimeout()\0"
    "info\0positionUpdatedHandler(QGeoPositionInfo)\0"
    "showFriends()\0onInvokeResult()\0value\0"
    "setGeoLocationInterval(float)\0Provider\0"
    "currentProvider\0QString\0pageContent\0"
    "viewModeTitle\0viewMode\0double\0myLat\0"
    "myLon\0GoogleMaps\0BingMaps\0OpenLayers\0"
};

void WebMaps::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WebMaps *_t = static_cast<WebMaps *>(_o);
        switch (_id) {
        case 0: _t->currentProviderChanged(); break;
        case 1: _t->viewModeChanged(); break;
        case 2: _t->gotMyLocation((*reinterpret_cast< const QGeoCoordinate(*)>(_a[1]))); break;
        case 3: _t->myLocationChanged((*reinterpret_cast< const QGeoCoordinate(*)>(_a[1]))); break;
        case 4: _t->subscribe(); break;
        case 5: _t->unsubscribe(); break;
        case 6: _t->friendLocationChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 7: _t->nextViewMode(); break;
        case 8: _t->positionUpdateTimeout(); break;
        case 9: _t->positionUpdatedHandler((*reinterpret_cast< const QGeoPositionInfo(*)>(_a[1]))); break;
        case 10: _t->showFriends(); break;
        case 11: _t->onInvokeResult(); break;
        case 12: _t->setGeoLocationInterval((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WebMaps::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WebMaps::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WebMaps,
      qt_meta_data_WebMaps, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WebMaps::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WebMaps::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WebMaps::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WebMaps))
        return static_cast<void*>(const_cast< WebMaps*>(this));
    return QObject::qt_metacast(_clname);
}

int WebMaps::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< Provider*>(_v) = currentProvider(); break;
        case 1: *reinterpret_cast< QString*>(_v) = pageContent(); break;
        case 2: *reinterpret_cast< QString*>(_v) = viewModeTitle(); break;
        case 3: *reinterpret_cast< QString*>(_v) = viewMode(); break;
        case 4: *reinterpret_cast< double*>(_v) = getMyLatitude(); break;
        case 5: *reinterpret_cast< double*>(_v) = getMyLongitude(); break;
        }
        _id -= 6;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setCurrentProvider(*reinterpret_cast< Provider*>(_v)); break;
        }
        _id -= 6;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void WebMaps::currentProviderChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void WebMaps::viewModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void WebMaps::gotMyLocation(const QGeoCoordinate & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WebMaps::myLocationChanged(const QGeoCoordinate & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WebMaps::subscribe()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void WebMaps::unsubscribe()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void WebMaps::friendLocationChanged(const QString & _t1, double _t2, double _t3, int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
