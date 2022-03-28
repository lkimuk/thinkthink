#include "VideoCategoryController.h"

#include <FileSender.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <VideoCategoryModel.h>
#include <VideoController.h>
#include <VideoModel.h>


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
    qmlRegisterType<VideoModel>("com.video.model", 1, 0, "VideoModel");

    VideoCategoryController* videoCateogryController = new VideoCategoryController(&engine);
    VideoController* videoController = new VideoController(&engine);
    videoController->addVideo(Video("Title1", "Neo", "2-25"));
    videoController->addVideo(Video("Title2", "Tom", "3-24"));
    videoController->addVideo(Video("Title3", "哈哈", "3-25"));
    videoController->addVideo(Video("Title4", "Kitty", "3-25"));
    videoController->addVideo(Video("Title5", "Neo", "4-25"));
    videoController->addVideo(Video("Title5", "Neo", "4-25"));
    videoController->addVideo(Video("Title5", "Neo", "4-25"));
    videoController->addVideo(Video("Title5", "Neo", "4-25"));
    videoController->addVideo(Video("Title5", "Neo", "4-25"));
    videoController->addVideo(Video("Title5", "Neo", "4-25"));
    videoController->addVideo(Video("Title5", "Neo", "4-25"));
    videoController->addVideo(Video("Title5", "Neo", "4-25"));
    videoController->addVideo(Video("Title5", "Neo", "4-25"));
    videoController->addVideo(Video("Title5", "Neo", "4-25"));
    videoController->addVideo(Video("Title5", "Neo", "4-25"));
    videoController->addVideo(Video("Title5", "Neo", "4-25"));
    videoController->addVideo(Video("Title5", "Neo", "4-25"));
    videoController->addVideo(Video("Title5", "Neo", "4-25"));

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("videoCategoryController", videoCateogryController);
    context->setContextProperty("videoController", videoController);


    const QUrl url(QStringLiteral("qrc:/assets/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    videoCateogryController->setVideoController(videoController);

    engine.load(url);

    return app.exec();
}
