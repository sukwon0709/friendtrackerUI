/* Copyright (c) 2013 Research In Motion Limited.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#include "WebMaps.hpp"

#include <QDebug>
#include <QFile>

#include <bb/location/PositionErrorCode>

#include <iostream>

using namespace bb::system;
using namespace QtMobilitySubset;
using namespace std;

//! [0]
WebMaps::WebMaps(QObject *parent)
    : QObject(parent)
    , m_currentProvider(BingMaps)
    , m_currentViewModeIndex(0)
	, m_positionInfoSource(QGeoPositionInfoSource::createDefaultSource(parent))
	, m_ProgressDialog(new SystemProgressDialog(this))
	, initialized(false)
{

//! [0]

    // Bing Maps
    {
        QVariantMap entry;
        entry["scriptFile"] = QLatin1String("local:///assets/bing_map.js");
        entry["mapUrl"] = QLatin1String("http://ecn.dev.virtualearth.net/mapcontrol/mapcontrol.ashx?v=7.0&mkt=en-gb");

        QVariantList viewModes;
        {
            QVariantMap viewMode;
            viewMode["title"] = tr("Auto");
            viewMode["mapType"] = QLatin1String("Microsoft.Maps.MapTypeId.auto");
            viewModes << viewMode;
        }
        {
            QVariantMap viewMode;
            viewMode["title"] = tr("Aerial");
            viewMode["mapType"] = QLatin1String("Microsoft.Maps.MapTypeId.aerial");
            viewModes << viewMode;
        }
        {
            QVariantMap viewMode;
            viewMode["title"] = tr("Birds Eye");
            viewMode["mapType"] = QLatin1String("Microsoft.Maps.MapTypeId.birdsEye");
            viewModes << viewMode;
        }
        {
            QVariantMap viewMode;
            viewMode["title"] = tr("Collins Bart");
            viewMode["mapType"] = QLatin1String("Microsoft.Maps.MapTypeId.collinsBart");
            viewModes << viewMode;
        }
        {
            QVariantMap viewMode;
            viewMode["title"] = tr("Mercator");
            viewMode["mapType"] = QLatin1String("Microsoft.Maps.MapTypeId.mercator");
            viewModes << viewMode;
        }
        {
            QVariantMap viewMode;
            viewMode["title"] = tr("Ordnance Survey");
            viewMode["mapType"] = QLatin1String("Microsoft.Maps.MapTypeId.ordnanceSurvey");
            viewModes << viewMode;
        }
        {
            QVariantMap viewMode;
            viewMode["title"] = tr("Road");
            viewMode["mapType"] = QLatin1String("Microsoft.Maps.MapTypeId.road");
            viewModes << viewMode;
        }
        entry["viewModes"] = viewModes;

        m_providerData.insert(BingMaps, entry);
    }

    // OpenLayers
    {
        QVariantMap entry;
        entry["scriptFile"] = QLatin1String("local:///assets/openlayers_map.js");
        entry["mapUrl"] = QLatin1String("http://openlayers.org/api/OpenLayers.js");

        QVariantList viewModes;
        {
            QVariantMap viewMode;
            viewMode["title"] = tr("Default");
            viewMode["mapType"] = QLatin1String("dummy");
            viewModes << viewMode;
        }
        entry["viewModes"] = viewModes;

        m_providerData.insert(OpenLayers, entry);
    }
}

//! [2]
void WebMaps::nextViewMode()
{
    const QVariantMap &entry = m_providerData[m_currentProvider];
    const QVariantList viewModes = entry["viewModes"].toList();

    m_currentViewModeIndex = ((m_currentViewModeIndex + 1) % viewModes.count());

    emit viewModeChanged();
}
//! [2]

WebMaps::Provider WebMaps::currentProvider() const
{
    return m_currentProvider;
}

//! [3]
void WebMaps::setCurrentProvider(Provider provider)
{
    if (m_currentProvider == provider)
        return;

    m_currentProvider = provider;
    m_currentViewModeIndex = 0;

    emit currentProviderChanged();
    emit viewModeChanged();
}
//! [3]

//! [4]
QString WebMaps::pageContent() const
{

	m_ProgressDialog->setState(SystemUiProgressState::Active);
	m_ProgressDialog->setEmoticonsEnabled(true);
	m_ProgressDialog->setTitle(tr("Initializing Bing Maps..."));
	m_ProgressDialog->cancelButton()->setLabel(tr("Cancel"));
	m_ProgressDialog->confirmButton()->setLabel(QString::null);

    const QVariantMap &entry = m_providerData[m_currentProvider];

    m_ProgressDialog->setBody("loading map file...");
    m_ProgressDialog->setProgress(30);
    m_ProgressDialog->show();

    QFile file("app/native/assets/map.html");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Unable to open map template file";
        return QString();
    }

    // Replace placeholders with data from current provider
    QByteArray content = file.readAll();
    content.replace("$$SCRIPT_FILE$$", entry["scriptFile"].toByteArray());
    content.replace("$$MAP_URL$$", entry["mapUrl"].toByteArray());

    // Start getting current location
    if (m_positionInfoSource == 0) {
    	return QString("Could not create QGeoPositionInfoSource!");
    }

    bool updateTimeoutConnected = connect(m_positionInfoSource,
    		SIGNAL(updateTimeout()),
    		this,
    		SLOT(positionUpdateTimeout()));
    Q_ASSERT(updateTimeoutConnected);
    Q_UNUSED(updateTimeoutConnected);
    cout << "updateTimeout signal connected" << endl;

    bool positionUpdatedConnected = connect(m_positionInfoSource,
    		SIGNAL(positionUpdated(const QGeoPositionInfo &)),
    		this,
    		SLOT(positionUpdatedHandler(const QGeoPositionInfo &)));
    Q_ASSERT(positionUpdatedConnected);
    Q_UNUSED(positionUpdatedConnected);
    cout << "positionUpdated signal connected" << endl;

    m_positionInfoSource->startUpdates();		// start get my location event loop

    m_ProgressDialog->setBody("getting current location...");
    m_ProgressDialog->setProgress(60);
    SystemUiResult::Type result = m_ProgressDialog->exec();

    if (result != SystemUiResult::ConfirmButtonSelection) {
    	cout << "initialization error!" << endl;
    	return QString();
    }

    // initialize bing map to my current location
    content.replace("$$INIT_LAT$$", QByteArray::number(myLocation.latitude()));
    content.replace("$$INIT_LNG$$", QByteArray::number(myLocation.longitude()));

    return QString::fromUtf8(content);
}
//! [4]

//! [5]
QString WebMaps::viewModeTitle() const
{
    const QVariantMap &entry = m_providerData[m_currentProvider];
    const QVariantList viewModes = entry["viewModes"].toList();

    return viewModes[m_currentViewModeIndex].toMap()["title"].toString();
}

QString WebMaps::viewMode() const
{
    const QVariantMap &entry = m_providerData[m_currentProvider];
    const QVariantList viewModes = entry["viewModes"].toList();

    return viewModes[m_currentViewModeIndex].toMap()["mapType"].toString();
}
//! [5]

void WebMaps::positionUpdateTimeout()
{
	cout << "TIMEOUT!!!!" << endl;
	m_ProgressDialog->setBody("initialization timeout");
	m_ProgressDialog->setState(SystemUiProgressState::Error);
	m_ProgressDialog->show();

	if ( m_positionInfoSource->property("replyErrorCode").isValid()  ) {
	    bb::location::PositionErrorCode::Type errorCode = m_positionInfoSource->property("replyErrorCode").value<bb::location::PositionErrorCode::Type>();
	    cout << "LM Error Code: ";
	    switch ( errorCode ) {
	        // this error code should not be encountered here (included for completeness)
	        case bb::location::PositionErrorCode::None:
	            cout << "None" << endl;
	            break;

	        case bb::location::PositionErrorCode::FatalDisabled:
	            cout << "Fatal - disabled (turn on location services!)" << endl;
	            break;

	        // this error code should not normally be encountered, may require setting
	        // the reset property to resolve.
	        case bb::location::PositionErrorCode::FatalInsufficientProviders:
	            cout << "Fatal - insufficient providers" << endl;
	            break;

	        // this error code could be encountered if an invalid value is set for a
	        // property related to a BB10 Location Manager feature.
	        case bb::location::PositionErrorCode::FatalInvalidRequest:
	            cout << "Fatal - invalid request" << endl;
	            break;

	        // the following warning codes are simply to provide more information;
	        // if periodic updates are active they will resume when conditions change.
	        // It may be opportune to inform the user that finding the location is
	        // taking longer than expected.
	        case bb::location::PositionErrorCode::WarnTimeout:
	            cout << "Warning - timeout" << endl;
	            break;

	        case bb::location::PositionErrorCode::WarnLostTracking:
	            cout << "Warning - lost tracking" << endl;
	            break;

	        default:
	            cout << "Unknown (bad enum value)" << endl;
	            break;
	    }
	}
}

void WebMaps::positionUpdatedHandler(const QGeoPositionInfo& update)
{
	cout << "SUCCESS " << update.coordinate().latitude() << "," << update.coordinate().longitude() << endl;
	myLocation = update.coordinate();

	if (!initialized) {
		m_ProgressDialog->setBody("initialization complete");
		m_ProgressDialog->setProgress(100);
		m_ProgressDialog->cancelButton()->setLabel(QString::null);
		m_ProgressDialog->confirmButton()->setLabel(tr("Ok"));
		m_ProgressDialog->setState(SystemUiProgressState::Inactive);
		m_ProgressDialog->show();

		emit gotMyLocation(update.coordinate());

		initialized = true;
	} else {
		emit myLocationChanged(myLocation);
	}
}

double WebMaps::getMyLatitude() const
{
	return myLocation.latitude();
}

double WebMaps::getMyLongitude() const
{
	return myLocation.longitude();
}