#include "VideoCategoryController.h"

#include <VideoCategoryModel.h>


VideoCategoryController::VideoCategoryController(QObject *parent)
    : QObject{parent}
{
    videoCategoryModel = new VideoCategoryModel();
}

void VideoCategoryController::addCategory(const QString &categoryName)
{
    videoCategoryModel->addCategory(categoryName);
}

VideoCategoryModel* VideoCategoryController::model() const
{
    return videoCategoryModel;
}

bool VideoCategoryController::empty() const
{
    return videoCategoryModel->rowCount() == 0 ? true : false;
}

QString VideoCategoryController::at(int index) const
{
    return videoCategoryModel->at(index);
}

void VideoCategoryController::setVideoController(VideoController *controller) const
{
    videoCategoryModel->setVideoController(controller);
}
