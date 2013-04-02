/*
 * Profile.cpp
 *
 *  Created on: 2013-03-23
 *      Author: Sukwon Oh
 */


#include "Profile.hpp"

#include "RegistrationHandler.hpp"

#include <bb/ImageData>

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/platform/bbm/Context>

using namespace bb::cascades;

//! [0]
Profile::Profile(bb::platform::bbm::Context &context, QObject *parent)
    : QObject(parent)
    , m_userProfile(0)
    , m_context(&context)
{
    // Load the place holder for the display image (avatar)
    // Image by Decosigner: http://openclipart.org/detail/104977/help-orb-button-by-decosigner
    m_displayPicture = bb::cascades::Image(QUrl("asset:///images/avatarPlaceholder.png"));
}
//! [0]

//! [1]
void Profile::show()
{
    // Grab the user's profile data
    m_userProfile = new bb::platform::bbm::UserProfile(m_context, this);

    // Make sure the UI is updated whenever the profile changes
    connect(m_userProfile, SIGNAL(displayNameUpdated(QString)),
            this, SIGNAL(profileChanged()));
    connect(m_userProfile, SIGNAL(personalMessageUpdated(QString)),
            this, SIGNAL(profileChanged()));
    connect(m_userProfile, SIGNAL(statusUpdated(bb::platform::bbm::UserStatus::Type, QString)),
            this, SIGNAL(profileChanged()));
    connect(m_userProfile, SIGNAL(displayPictureUpdated(bb::platform::bbm::ImageType::Type, QByteArray)),
            this, SIGNAL(profileChanged()));

    // Create the UI
    QmlDocument* qml = QmlDocument::create("asset:///profile.qml").parent(this);
    qml->setContextProperty("_profile", this);

    AbstractPane* root = qml->createRootObject<AbstractPane>();
    Application::instance()->setScene(root);
}
//! [1]

//! [2]
void Profile::requestDisplayPicture()
{
    const QByteArray imageData = m_userProfile->displayPicture();

    m_displayPicture = bb::cascades::Image(imageData);
    emit profileChanged();
}
//! [2]

//! [3]
bool Profile::busy() const
{
    return (m_userProfile->status() == bb::platform::bbm::UserStatus::Busy);
}

QString Profile::displayName() const
{
    return m_userProfile->displayName();
}
//! [3]

QString Profile::statusMessage() const
{
    return m_userProfile->statusMessage();
}

QString Profile::personalMessage() const
{
    return m_userProfile->personalMessage();
}

QString Profile::ppid() const
{
    return m_userProfile->ppId();
}

QString Profile::appVersion() const
{
    return m_userProfile->applicationVersion();
}

QString Profile::handle() const
{
    return m_userProfile->handle();
}

QString Profile::platformVersion() const
{
    return QString::number(m_userProfile->sdkVersion());
}

QVariant Profile::displayPicture() const
{
    return QVariant::fromValue(m_displayPicture);
}


