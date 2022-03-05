#include "VideoCategoryController.h"

#include <VideoCategoryModel.h>


VideoCategoryController::VideoCategoryController(QObject *parent)
    : QObject{parent}
{
    videoCategoryModel = new VideoCategoryModel();
    videoCategoryModel->addCategory("Hahsh");
    videoCategoryModel->addCategory("sjalfkjas");
}

VideoCategoryModel* VideoCategoryController::model() const
{
    return videoCategoryModel;
}
