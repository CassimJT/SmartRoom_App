#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "systemcontroller.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    SystemController systemcontroller;
    engine.rootContext()->setContextProperty("Systemcontroller", &systemcontroller);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("SmartRoom", "Main");

    return app.exec();
}
