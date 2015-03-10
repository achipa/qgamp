#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "../../src/googlemp.h"

// define the singleton type provider function (callback).
static QObject *analytics_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    qDebug() << "Creating/getting GoogleMP singleton";
    GoogleMP *gmp = GoogleMP::instance();
    return gmp;
}

int main(int argc, char *argv[])
{
    // we're getting a timestamp as early as possible, to be able to do startup timings
    qint64 imAlive = QDateTime::currentMSecsSinceEpoch();

    QApplication app(argc, argv);

    // QApplication level app name and version are used automatically in reports
    qApp->setApplicationName("HelloQGAMP");
    qApp->setApplicationVersion("1.0");
    qApp->setOrganizationDomain("csipa.net");
    qApp->setOrganizationName("qgamp");

    // start session
    GoogleMP::startSession(imAlive);

    QQmlApplicationEngine engine;

    // register qgamp to be available to QML apps
    qmlRegisterSingletonType<GoogleMP>("MeasurementProtocol", 1, 0, "Analytics", analytics_singletontype_provider);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // can be used from C++ (see main.qml for QML usage example)
    GoogleMP::instance()->reportEvent("Test", "CPP_call", "1");

    return app.exec();
}
