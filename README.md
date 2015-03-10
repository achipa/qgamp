# QGAMP

QGAMP is a Qt/QML interface for the Google Analytics Measurement Protocol


Google provides a platform-independent HTTP API to process data - the Google Measurement Protocol

https://developers.google.com/analytics/devguides/collection/protocol/v1/

QGAMP is a C++ class (API) that provides a convenient API for Qt Applications to be able to use
Google Analytics interfaces to review timings, events and general user interaction patterns from
both C++ and QML. 

It's cross platform, and able to report from all Qt-supported platforms (so far verified on 
Android, iOS and Linux).

The requests are issued asynchronously through a network request queue, so they would not interfere
with normal operations of the application.

If operated offline, QGAMP can maintain a timestamped buffer, and replay that buffer (with the
correct timestamps) when the application is started later when connectivity is restored. Note that 
the buffer size is limited and increasing it is not advised as Google Analytics will throttle 
clients if too many requests are issued in short periods of time.

Example:

= C++

	#include "googlemp.h"
	...
	// QApplication level app name and version are used automatically in reports
	qApp->setApplicationName("HelloQGAMP");
	qApp->setApplicationVersion("1.0");
	qApp->setOrganizationDomain("csipa.net");
	qApp->setOrganizationName("qgamp");

	// start session
	GoogleMP::startSession(QDateTime::currentMSecsSinceEpoch());

	GoogleMP::instance()->reportEvent("Test", "CPP_call", "1");

= QML

In main.cpp we need to initialize and register

	static QObject *analytics_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
	{
	    Q_UNUSED(engine)
	    Q_UNUSED(scriptEngine)

	    GoogleMP *gmp = GoogleMP::instance();
	    return gmp;
	}
	
	int main(int argc, char *argv[])
	{
	    ...
	    qApp->setApplicationName("HelloQGAMP");
	    qApp->setApplicationVersion("1.0");
	    qApp->setOrganizationDomain("csipa.net");
	    qApp->setOrganizationName("qgamp");

	    GoogleMP::startSession(QDateTime::currentMSecsSinceEpoch());

	    qmlRegisterSingletonType<GoogleMP>("MeasurementProtocol", 1, 0, "Analytics", analytics_singletontype_provider);
	    ...
	}

After this, we can inclue the following in the QML files:

	import MeasurementProtocol 1.0

And then use the Analytics object to access all methods. Note that qgamp registers as a singleton, 
so you don't need to create analytics items, the Analytics object becomes available just by having
the import statement

	
    Component.onCompleted: {
        // A good way to time QML startup performance
        Analytics.reportTiming("startup_QML", false);

        // use showScreen to track user navigation
        // note: onCompleted is only good for first screen
        Analytics.showScreen("ApplicationWindow");
    }


For a detailed example of mixes C++ and QML use of qgamp, take a look at the example directory





DISCLAIMER: This project is not written nor endorsed by Google. It does not contain any SDK or 
code from Google - it creates and executes all requests autonomously.

Google Analytics™ service is a trademark of Google Inc.
Google and the Google logo are registered trademarks of Google Inc., used with permission.
