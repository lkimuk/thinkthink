#include "VideoController.h"
#include "VideoModel.h"


VideoController::VideoController(QObject *parent)
    : QObject{parent}
{
    videoModel = new VideoModel();
}

void VideoController::addVideo(const Video &video)
{
    videoModel->addVideo(video);
}

VideoModel *VideoController::model() const
{
    return videoModel;
}

void VideoController::updateVideos(const QString &category)
{
    videoModel->updateVideos(category);
}
