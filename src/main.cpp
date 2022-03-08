#include "VideoCategoryController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <VideoCategoryModel.h>


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

//    VideoCategoryModel *model = new VideoCategoryModel();
//    model->addCategory("Hahsh");
//    model->addCategory("sjalfkjas");

//    QQmlContext *context = engine.rootContext();
//    context->setContextProperty("mymodel", model);

    qmlRegisterType<VideoCategoryModel>("com.video.category.model", 1, 0,
                                                   "VideoCategoryModel");

    VideoCategoryController* videoCateogryController = new VideoCategoryController(&engine);
    videoCateogryController->addCategory("First");
    videoCateogryController->addCategory("Second");
    videoCateogryController->addCategory("Third");
    videoCateogryController->addCategory("First");
    videoCateogryController->addCategory("First");
    videoCateogryController->addCategory("First");
    videoCateogryController->addCategory("First");
    videoCateogryController->addCategory("First");
    videoCateogryController->addCategory("First");
    videoCateogryController->addCategory("First");
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("videoCategoryController", videoCateogryController);


    const QUrl url(QStringLiteral("qrc:/src/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
