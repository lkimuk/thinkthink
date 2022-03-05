#ifndef VIDEOCATEGORYCONTROLLER_H
#define VIDEOCATEGORYCONTROLLER_H

#include <QObject>

class VideoCategoryModel;


class VideoCategoryController : public QObject
{
    Q_OBJECT

public:
    explicit VideoCategoryController(QObject *parent = nullptr);
    Q_INVOKABLE VideoCategoryModel* model() const;

//signals:
//    void modelChanged();

private:
    VideoCategoryModel* videoCategoryModel;
};

#endif // VIDEOCATEGORYCONTROLLER_H
