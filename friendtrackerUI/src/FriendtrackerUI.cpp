// Navigation pane project template
#include "FriendtrackerUI.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/platform/bbm/ContactService>
#include <bb/platform/bbm/Contact>
#include <bb/platform/bbm/UserProfile>
#include <bb/platform/bbm/MessageService>
#include <bb/pim/contacts/ContactService>
#include <bb/pim/contacts/Contact>
#include <bb/pim/contacts/ContactListFilters>

#include "LoginMessage.h"
#include "UpdateLocationMessage.h"
#include "ServerInterface.h"

#include <iostream>
using namespace std;

using namespace bb::cascades;
using namespace bb::platform::bbm;

FriendtrackerUI::FriendtrackerUI(bb::cascades::Application *app, const QString& uuid)
: QObject(app)
, m_app(app)
, m_uuid(uuid)
, m_webMaps(new WebMaps(this))
, m_regHandler(new RegistrationHandler(m_uuid, m_webMaps, this))
, m_profile(0)
, m_sessionKey("")
, m_serverInterface(new ServerInterface(this))

{
	// get user profile when bbm registration succeeds
	bool connected = QObject::connect(m_regHandler, SIGNAL(registered()), this, SLOT(initUserProfile()));
	Q_ASSERT(connected);

	// load main.qml when bbm registration succeeds
	connected = QObject::connect(m_regHandler, SIGNAL(registered()), this, SLOT(initWebMaps()));
	Q_ASSERT(connected);

	// login when user location is retrieved
	connected = QObject::connect(m_webMaps,
			SIGNAL(gotMyLocation(const QGeoCoordinate &)),
			this,
			SLOT(login(const QGeoCoordinate &)));
	Q_ASSERT(connected);

	// update location whenever user's location is updated (every 5 sec by default?)
	connected = QObject::connect(m_webMaps,
			SIGNAL(myLocationChanged(const QGeoCoordinate &)),
			this,
			SLOT(updateLocation(const QGeoCoordinate &)));
	Q_ASSERT(connected);

	// get session key from login
	connected = QObject::connect(m_serverInterface,
			SIGNAL(loginSuccess(const QString &)),
			this,
			SLOT(setSessionKey(const QString &)));
	Q_ASSERT(connected);
	Q_UNUSED(connected);
}

void FriendtrackerUI::login(const QGeoCoordinate& coord)
{
	LoginMessage msg(m_profile->ppId(),
			coord.latitude(),
			coord.longitude());

	m_serverInterface->sendMessage(msg);
}

void FriendtrackerUI::setSessionKey(const QString& sessionKey)
{
	m_sessionKey = sessionKey;
}

void FriendtrackerUI::updateLocation(const QGeoCoordinate& coord)
{
	UpdateLocationMessage msg(m_profile->ppId(),
			coord.latitude(),
			coord.longitude(),
			m_sessionKey);

	m_serverInterface->sendMessage(msg);
}

void FriendtrackerUI::initWebMaps()
{
	cout << "initWebMaps started" << endl;
    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(m_app);
    qml->setContextProperty("_mapView", m_webMaps);

    // create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    // set created root object as a scene
    m_app->setScene(root);
}

void FriendtrackerUI::initUserProfile()
{
	m_profile = new UserProfile(&m_regHandler->context(), this);
	cout << "my display name: " << m_profile->displayName().toStdString() << endl;
	cout << "my personal msg: " << m_profile->personalMessage().toStdString() << endl;
	cout << "my status msg: " << m_profile->statusMessage().toStdString() << endl;
	cout << "my ppId: " << m_profile->ppId().toStdString() << endl;

	ContactService cs(&m_regHandler->context(), 0);
	if (cs.isValid()) cout << "contact service is valid " << cs.contactCount() << endl;
	QList<Contact> contacts = cs.contacts();
	vector<QString> ppIds;
	cout << "getting contacts" << endl;
	for (int i = 0; i < contacts.size(); i++) {
		cout << "ppId: " << contacts.at(i).ppId().toStdString()
			 << " displayName: " << contacts.at(i).displayName().toStdString()
			 << endl;
		ppIds.push_back(contacts.at(i).ppId());
	}
	/*using namespace bb::pim;
	bb::pim::contacts::ContactListFilters filter;
	filter = filter.setLimit(10000);
	QList<bb::pim::contacts::Contact> contacts = bb::pim::contacts::ContactService().contacts(filter);
	for (int i = 0; i < contacts.size(); i++) {
		contacts::Contact detailedContact = contacts::ContactService().contactDetails(contacts.at(i).id());
		cout << "name: " << contacts.at(i).displayName().toStdString()
			 << " account id: " << contacts.at(i).accountId() << endl;
		QList<contacts::ContactAttribute> attributes = detailedContact.attributes();
		for (int j = 0; j < attributes.size(); j++) {
			cout << attributes.at(j).label().toStdString() << ": "
					<< attributes.at(j).value().toStdString() << endl;
		}
	}*/

	emit userProfileInitialized();
}
