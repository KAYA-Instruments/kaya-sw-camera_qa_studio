#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "RawPixelModel.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<RawPixelModel>("RawTwin", 1, 0, "RawPixelModel");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Main.qml"_qs);

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl) QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);
    return app.exec();
}
