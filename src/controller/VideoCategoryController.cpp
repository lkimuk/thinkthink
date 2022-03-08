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
