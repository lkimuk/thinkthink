#include "VideoModel.h"
#include <QTcpSocket>
#include <RequestMessage.h>


Video::Video(const QString &title, const QString &uploader, const QString &upload_date)
    : m_title(title), m_uploader(uploader), m_uploadDate(upload_date)
{
}

QString Video::title() const
{
    return m_title;
}

QString Video::uploader() const
{
    return m_uploader;
}

QString Video::upload_date() const
{
    return m_uploadDate;
}


VideoModel::VideoModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_socket = new QTcpSocket();
    connect(m_socket, &QTcpSocket::disconnected, this, &VideoModel::closeSocket);
    connect(m_socket, &QTcpSocket::readyRead, this, &VideoModel::responseData);
    m_socket->connectToHost("127.0.0.1", 3007);
}

void VideoModel::addVideo(const Video &video)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_videos << video;
    endInsertRows();
}

int VideoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_videos.count();
}

QVariant VideoModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_videos.count())
        return QVariant();

    const Video& video = m_videos[index.row()];
    if(role == TitleRole)
        return video.title();
    else if(role == UploaderRole)
        return video.uploader();
    else if(role == UploadDateRole)
        return video.upload_date();
    return QVariant();
}

void VideoModel::updateVideos(const QString &category)
{
    qDebug() << "entry updateVideos" << category;

    RequestMessage request;
    request.setMessage(RequestMessage::RequestType, "GetVideos");
    request.setMessage(RequestMessage::VideoCategory, category.toStdString().c_str());
    request.commit();

    qDebug() << request.data();
}

void VideoModel::closeSocket()
{
    m_socket->close();
}

void VideoModel::responseData()
{

}

QHash<int, QByteArray> VideoModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[UploaderRole] = "uploader";
    roles[UploadDateRole] = "upload_date";
    return roles;
}


