#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QTimer>
#include <QMqttClient>

class SystemController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double temp READ temp WRITE setTemp NOTIFY tempChanged FINAL)

public:
    explicit SystemController(QObject *parent = nullptr);
    ~SystemController();

    double temp() const;
    void setTemp(double newTemp);

public slots:
    void replayReadyRead();
    void errorOccurred(QNetworkReply::NetworkError code);
    void fetchTemp();

    void mqttConnected();
    void mqttDisconnected();
    void onMqttMessageReceived(const QByteArray &message, const QMqttTopicName &topic);
    void errorOccured(QMqttClient::ClientError error);
    void publishFanState(bool state);

signals:

    void tempChanged();
    void error(QString error);

private:
    QNetworkAccessManager *manager = nullptr;
    QNetworkReply *replay = nullptr;
    QTimer *m_timer;
    double m_temp;
    QMqttClient *mqttCLient = nullptr;

};

#endif // SYSTEMCONTROLLER_H
