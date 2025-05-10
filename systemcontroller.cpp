#include "systemcontroller.h"

SystemController::SystemController(QObject *parent)
    : QObject{parent}, m_temp(0.0)
{
    mqttCLient = new QMqttClient(this);
    mqttCLient->setHostname("192.168.8.116");
    mqttCLient->setPort(1883);
    mqttCLient->connectToHost();
    manager = new QNetworkAccessManager(this);
    m_timer = new QTimer(this);

    //connection
    connect(mqttCLient,&QMqttClient::connected, this,&SystemController::mqttConnected);
    connect(mqttCLient,&QMqttClient::disconnected, this,&SystemController::mqttDisconnected);
    connect(mqttCLient,&QMqttClient::errorChanged, this,&SystemController::errorOccured);
    connect(mqttCLient,&QMqttClient::messageReceived, this,&SystemController::onMqttMessageReceived);

    //connect(m_timer,&QTimer::timeout,this,&SystemController::fetchTemp);
    //m_timer->start(2000);

}

SystemController::~SystemController()
{
    //the distractore
    delete manager;
    delete mqttCLient;

}

void SystemController::replayReadyRead()
{
    if(!replay){
        qDebug()<<"Replay Canceled";
        return;
    }
    if(replay->error() == QNetworkReply::NoError){
        auto data = replay->readAll();
        if(!data.isEmpty()) {
            QJsonDocument jsondoc = QJsonDocument::fromJson(data);
            if(jsondoc.isArray()) {
                QJsonArray arr = jsondoc.array();
                if(!arr.isEmpty()) {
                    QJsonObject lastobj = arr.at(0).toObject();
                    double latestTemp = lastobj["temp"].toDouble();
                    setTemp(latestTemp);
                }
            }

        }else{
            qDebug()<<"No temperature readding";
        }
    }else {
        qDebug()<<"Error:" <<replay->errorString();
    }
    replay->deleteLater();
}
/**
 * @brief SystemController::errorOcurred
 * nadle the error
 */
void SystemController::errorOccurred(QNetworkReply::NetworkError code)
{
    QString m_error = replay->errorString();
    emit error(m_error);
}

/**
 * @brief SystemController::fetchTemp
 * fetch the temperature form the api
 */
void SystemController::fetchTemp()
{
    replay = manager->get(QNetworkRequest(QUrl("http://192.168.8.116:3000/api/iot/temp")));
    connect(replay,&QNetworkReply::readyRead,this,&SystemController::replayReadyRead);
    connect(replay,&QNetworkReply::errorOccurred, this, &SystemController::errorOccurred);

}
/**
 * @brief SystemController::mqttConnected
 * connected
 */
void SystemController::mqttConnected()
{
    qDebug()<<"Connected to mqtt";
    auto subscription = mqttCLient->subscribe(QMqttTopicFilter("iot/temp"),0);
    if(!subscription) {
        qDebug() << "Faild to subscribe";
    }

}
/**
 * @brief SystemController::mqttDisconnected
 * disconnected
 */
void SystemController::mqttDisconnected()
{
    qDebug() << "Disconnected from MQTT broker.";
}
/**
 * @brief SystemController::onMqttMessageReceived
 * @param message
 * @param topic
 */
void SystemController::onMqttMessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    qDebug() << "Received message on topic" << topic.name() << ":" << message;
    QJsonDocument jsondoc = QJsonDocument::fromJson(message);
    if (jsondoc.isObject()) {
        QJsonObject obj = jsondoc.object();
        if (obj.contains("temp") && obj["temp"].isDouble()) {
            double latestTemp = obj["temp"].toDouble();
            setTemp(latestTemp);
        }
    }
}
/**
 * @brief SystemController::errorOccured
 * when error occure
 */
void SystemController::errorOccured(QMqttClient::ClientError error)
{
    qDebug() << "error:" << error;
}
/**
 * @brief SystemController::publishFanState
 * @param state
 * togole state
 */
void SystemController::publishFanState(bool state)
{
    QByteArray msg = state ? "on": "off";
    QMqttTopicName topic("iot/fan/state");
    if(mqttCLient->state() == QMqttClient::Connected) {
        mqttCLient->publish(topic,msg,0,false);
    }else {
        qDebug()<<" Server not connected ";
    }

}

double SystemController::temp() const
{
    return m_temp;
}

void SystemController::setTemp(double newTemp)
{
    if (qFuzzyCompare(m_temp, newTemp))
        return;
    m_temp = newTemp;
    emit tempChanged();
}
