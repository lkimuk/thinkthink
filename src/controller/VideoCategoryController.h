#ifndef VIDEOCATEGORYCONTROLLER_H
#define VIDEOCATEGORYCONTROLLER_H

#include <QObject>

class VideoCategoryModel;
class VideoController;


class VideoCategoryController : public QObject
{
    Q_OBJECT

public:
    explicit VideoCategoryController(QObject *parent = nullptr);
    void addCategory(const QString& categoryName);
    Q_INVOKABLE VideoCategoryModel* model() const;

    bool empty() const;

    QString at(int index) const;

    void setVideoController(VideoController* controller) const;

//signals:
//    void modelChanged();

private:
    VideoCategoryModel* videoCategoryModel;
};

#endif // VIDEOCATEGORYCONTROLLER_H
