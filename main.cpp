#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "qdebug.h"
#include "qdir.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImportPath("./plugins");
    engine.addImportPath("./plugins/QMLImageFx");
    qDebug()<< QDir::currentPath();
    qDebug()<< engine.importPathList();

   //принудительная загрузка плагина
   // QList<QQmlError>  qmlErrorList;
   // engine.importPlugin(QDir::currentPath()+"/plugins/QMLImageFX/QMLImageFx.dll","QMLImageFx",&qmlErrorList);
   // qDebug()<<qmlErrorList;
    app.setOrganizationName("myhome");
    app.setOrganizationDomain("myhome.ru");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
