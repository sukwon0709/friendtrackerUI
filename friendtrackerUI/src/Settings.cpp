/*
 * Settings.cpp
 *
 *  Created on: 2013-03-23
 *      Author: soh
 */


#include "Settings.hpp"
#include "RegistrationHandler.hpp"

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/platform/bbm/UserProfile>
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeManager>
#include <bb/system/CardDoneMessage>
#include <bb/system/InvokeTargetReply>
#include <bb/cascades/pickers/FilePicker>
#include <bb/utility/ImageConverter>
#include <bb/ImageData>

#include <bps/soundplayer.h>

#include <iostream>

using namespace std;

using namespace bb::cascades;
using namespace bb::platform;
using namespace bb::system;
using namespace bb::cascades::pickers;

Settings::Settings(QObject* parent, RegistrationHandler* regHandler)
: QObject(parent)
, m_parent(parent)
, m_regHandler(regHandler)
, m_userProfile(0)
, m_cameraInvokeStatus(0)
, m_filePicker(0)
, m_initialized(false)
{
	//qmlRegisterType < Camera > ("bb.cascades.multimedia", 1, 0, "Camera");
}

Settings::~Settings()
{

}

QString Settings::displayName()
{
	return m_displayName;
}

/*
 * Called when the user changes from Settings
 */
void Settings::setDisplayName(const QString& displayName)
{
	m_displayName = displayName;
	emit displayNameChanged(displayName);
}

/*
 * Called when the user changes from BBM
 */
void Settings::setDisplayNameFromBBM(const QString& displayName)
{
	m_displayName = displayName;
}

bb::cascades::Image Settings::profilePicture()
{
	return m_profilePicture;
}

/*
 * Called when the user changes from Settings
 */
void Settings::setProfilePicture(const bb::cascades::Image& profilePicture)
{
	cout << "setProfilePicture" << endl;
	m_profilePicture = profilePicture;
	bb::utility::ImageConverter imageConverter;
	bb::ImageData imageData = imageConverter.decode(profilePicture.source());
	QStringList splitList = profilePicture.source().toString().split(QRegExp("\\."));
	if (splitList.at(splitList.size()-1) == "jpg") {
		QByteArray byteData = imageConverter.encode("image/jpeg", imageData);
		m_userProfile->requestUpdateDisplayPicture(bbm::ImageType::Jpg, byteData);
	} else if (splitList.at(splitList.size()-1) == "png") {
		QByteArray byteData = imageConverter.encode("image/png", imageData);
		m_userProfile->requestUpdateDisplayPicture(bbm::ImageType::Png, byteData);
	} else if (splitList.at(splitList.size()-1) == "gif") {
		QByteArray byteData = imageConverter.encode("image/gif", imageData);
		m_userProfile->requestUpdateDisplayPicture(bbm::ImageType::Gif, byteData);
	} else if (splitList.at(splitList.size()-1) == "bmp") {
		QByteArray byteData = imageConverter.encode("image/bmp", imageData);
		m_userProfile->requestUpdateDisplayPicture(bbm::ImageType::Bmp, byteData);
	} else {
		//m_userProfile->requestUpdateDisplayPicture(bbm::ImageType::Unsupported, profilePicture);
	}
	emit profilePictureChanged(profilePicture);
}

/*
 * Called when the user changes from BBM
 */
void Settings::setProfilePictureFromBBM(bbm::ImageType::Type mimeType, const QByteArray& profilePicture)
{
	Q_UNUSED(mimeType);
	m_profilePicture = profilePicture;
	emit profilePictureChanged(profilePicture);
}

QString Settings::statusMessage()
{
	return m_statusMessage;
}

/*
 * Called when the user changes from Settings
 */
void Settings::setStatusMessage(const QString& statusMessage)
{
	cout << "setStatusMessage" << endl;
	m_statusMessage = statusMessage;
	bool result = false;
	if (statusMessage == "Busy") {
		result = m_userProfile->requestUpdateStatus(bbm::UserStatus::Busy, statusMessage);
		cout << "setStatusMessage - result: " << result << endl;
	} else {
		m_userProfile->requestUpdateStatus(bbm::UserStatus::Available, statusMessage);
		cout << "setStatusMessage - result: " << result << endl;
	}

	emit statusMessageChanged(statusMessage);
}

/*
 * Called when the user changes from BBM
 */
void Settings::setStatusMessageFromBBM(bbm::UserStatus::Type statusType, const QString& statusMessage)
{
	Q_UNUSED(statusType);
	m_statusMessage = statusMessage;
	emit statusMessageChangedFromBBM(statusMessage);
}

QString Settings::personalMessage()
{
	return m_personalMessage;
}

/*
 * Called when the user changes from Settings
 */
void Settings::setPersonalMessage(const QString& personalMessage)
{
	cout << "setPersonalMessage" << endl;
	m_personalMessage = personalMessage;
	m_userProfile->requestUpdatePersonalMessage(personalMessage);
	emit personalMessageChanged(personalMessage);
}

/*
 * Called when the user changes from BBM
 */
void Settings::setPersonalMessageFromBBM(const QString& personalMessage)
{
	m_personalMessage = personalMessage;
	emit personalMessageChanged(personalMessage);
}

void Settings::initUserProfileFromBBM()
{
	if (!m_initialized) {
		// get profile info
		m_userProfile = new bbm::UserProfile(&m_regHandler->context());
		bool result = connect(m_userProfile, SIGNAL(displayNameUpdated(const QString &)),
				this, SLOT(setDisplayNameFromBBM(const QString &)));
		Q_ASSERT(result);
		result = connect(m_userProfile, SIGNAL(statusUpdated(bb::platform::bbm::UserStatus::Type, const QString &)),
				this, SLOT(setStatusMessageFromBBM(bb::platform::bbm::UserStatus::Type, const QString &)));
		Q_ASSERT(result);
		result = connect(m_userProfile, SIGNAL(displayPictureUpdated(bb::platform::bbm::ImageType::Type, const QByteArray &)),
				this, SLOT(setProfilePictureFromBBM(bb::platform::bbm::ImageType::Type, const QByteArray &)));
		Q_ASSERT(result);
		result = connect(m_userProfile, SIGNAL(personalMessageUpdated(const QString &)),
				this, SLOT(setPersonalMessageFromBBM(const QString &)));
		Q_ASSERT(result);

		m_displayName = m_userProfile->displayName();
		m_profilePicture = m_userProfile->displayPicture();
		m_statusMessage = m_userProfile->statusMessage();
		m_personalMessage = m_userProfile->personalMessage();

		m_initialized = true;
	}

	// TODO: connect signal to BBM
}

/**
 * Open up a camera for taking Profile Picture
 */
void Settings::openCamera()
{
	InvokeManager* invokeManager = new InvokeManager(this);
	InvokeRequest request;
	request.setTarget("sys.camera.card");
	request.setAction("bb.action.CAPTURE");
	request.setData("photo");
	request.setTargetTypes(InvokeTarget::Card);
	InvokeTargetReply* reply = invokeManager->invoke(request);
	reply->setParent(this);
	connect(reply, SIGNAL(finished()), this, SLOT(onCameraInvokeResult()));
	connect(invokeManager, SIGNAL(childCardDone(const bb::system::CardDoneMessage &)),
			this, SLOT(cameraCardDone(const bb::system::CardDoneMessage &)));
	m_cameraInvokeStatus = reply;
}

void Settings::onCameraInvokeResult()
{
	// Check for errors
	    switch(m_cameraInvokeStatus->error()) {
	        // Invocation could not find the target
	        // did we use the right target ID?
	    case InvokeReplyError::NoTarget: {
	            cout << "invokeFinished(): Error: no target" << endl;
	            break;
	        }
	        // There was a problem with the invoke request
	        // did we set all the values correctly?
	    case InvokeReplyError::BadRequest: {
	            cout << "invokeFinished(): Error: bad request" << endl;
	            break;
	        }
	        // Something went completely
	        // wrong inside the invocation request
	        // Find an alternate route :(
	    case InvokeReplyError::Internal: {
	            cout << "invokeFinished(): Error: internal" << endl;
	            break;
	        }
	        //Message received if the invoke request is successful
	    default:
	        cout << "invokeFinished(): Invoke Succeeded" << endl;
	        break;
	    }

	    // A little house keeping never hurts...
	    delete m_cameraInvokeStatus;
}

/**
 * Camera cards responses
 * done - card is closed without initiating a capture
 * close - card closes due to error
 * save - card is closed after user takes a photo
 */
void Settings::cameraCardDone(const bb::system::CardDoneMessage& message)
{
	cout << "REASON: " << message.reason().toStdString() << endl;
	cout << "MESSAGE: " << message.data().toStdString() << endl;
	cout << "Type: " << message.dataType().toStdString() << endl;

	// FIXME: this is an ugly hack. dataType is "" for FilePicker
	// so I am checking that value to determine if I should create FilePicker
	if (message.reason() == "save" && message.dataType() != "") {
		m_filePicker = new FilePicker();
		m_filePicker->setType(FileType::Picture);
		m_filePicker->setTitle("Select Profile Picture");
		m_filePicker->setMode(FilePickerMode::Picker);
		m_filePicker->setImageCropEnabled(true);
		m_filePicker->open();

		connect(m_filePicker, SIGNAL(fileSelected(const QStringList &)),
				this, SLOT(updateProfilePicture(const QStringList &)));
	}
}

void Settings::updateProfilePicture(const QStringList& images)
{
	// only use first image
	if (images.size() > 0) {
		cout << "UPDATE: " << images.at(0).toStdString() << endl;
		setProfilePicture(Image(images.at(0)));
	}
}
