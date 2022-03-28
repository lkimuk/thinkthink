#ifndef VIDEOCONTROLLER_H
#define VIDEOCONTROLLER_H

#include <QObject>

class Video;
class VideoModel;
class VideoCategoryController;


class VideoController : public QObject
{
    Q_OBJECT
public:
    explicit VideoController(QObject *parent = nullptr);

    void addVideo(const Video& video);

    Q_INVOKABLE VideoModel* model() const;

    void updateVideos(const QString& category);


private:
    VideoModel* videoModel;

};

#endif // VIDEOCONTROLLER_H
