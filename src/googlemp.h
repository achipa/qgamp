#ifndef GOOGLEMP_H
#define GOOGLEMP_H

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QObject>
#include <QLocale>
#include <QSettings>
#include <QMutex>

class GoogleMP : public QObject
{
    Q_OBJECT
    Q_PROPERTY (uint startTime READ startTime)
    Q_PROPERTY (QString appName READ appName WRITE setAppName)
    Q_PROPERTY (QString appVersion READ appVersion WRITE setAppVersion)
    Q_PROPERTY (QString appId READ appId WRITE setAppId)

public:
    static void startSession(qint64 sTime, QVariantMap extSessionParams = QVariantMap());
    static qint64 startTime() { return m_startTime; }
    static QString divineUserAgent();
    static GoogleMP* m_Instance;

    explicit GoogleMP(QObject *parent = 0) ;
    ~GoogleMP() ;

    QString appVersion() { return m_appVersion; }
    QString appName() { return m_appName; }
    QString appId() { return m_appId; }
    void setAppVersion(QString appVersion) { m_appVersion = appVersion; }
    void setAppName(QString appName) { m_appName = appName; }
    void setAppId(QString appId) { m_appId = appId; }

    Q_INVOKABLE void showScreen(QString screenName) ;
    Q_INVOKABLE void startTiming(QString eventName, bool overwrite) ;
    Q_INVOKABLE void reportTiming(QString eventName, bool reset) ;
    Q_INVOKABLE void reportRawTiming(QString eventName, int msecs) ;
    Q_INVOKABLE void reportEvent(QString category, QString action, QString value) ;
    Q_INVOKABLE void sendRaw(QString rawstring) ;

    GoogleMP(const GoogleMP &); // hide copy constructor
    GoogleMP& operator=(const GoogleMP &); // hide assign op
                                 // we leave just the declarations, so the compiler will warn us
                                 // if we try to use those two functions by accident

    static GoogleMP* instance()
    {
        static QMutex mutex;
        if (!m_Instance)
        {
            mutex.lock();

            if (!m_Instance)
                m_Instance = new GoogleMP();

            mutex.unlock();
        }

        return m_Instance;
    }

    static void drop()
    {
        static QMutex mutex;
        mutex.lock();
        delete m_Instance;
        m_Instance = 0;
        mutex.unlock();
    }
signals:

public slots:
    void networkreply() ;

private:
    static qint64 m_startTime;
    static QVariantMap m_extParams;
    static QVariantMap m_extSessionParams;

    static bool isConnectedToNetwork();

    QNetworkReply *m_reply = 0;
    QNetworkAccessManager *m_manager = 0;
    QString m_uuid = "";

    QMap<QString, qint64> m_timers;
    QLocale m_locale;
    QString m_appName;
    QString m_appVersion;
    QString m_appId;
    int m_width = 0;
    int m_height= 0;
    QString m_ua = "";
    bool m_enabled = false;
    bool m_bufferfull = false;
    QSettings* m_settings;

    QByteArray vmapToPostData(QVariantMap top);
    void sendRequest(QByteArray postData);
    void appendCommonData(QVariantMap *base);
};

#endif // GOOGLEMP_H
