#include "VideoModel.h"
#include <QTcpSocket>
#include <RequestMessage.h>


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
    if(role == UploaderRole)
        return video.uploader;
    else if(role == UploadDateRole)
        return video.upload_date;
    else if(role == VideoNameRole)
        return video.video_name;
    else if(role == VideoIdRole)
        return video.video_id;
    else if(role == CoverImageRole)
        return video.cover_image;
    else if(role == SourceRole)
        return video.source;
    else if(role == DescribeRole)
        return video.describe;
    return QVariant();
}

void VideoModel::updateVideos(const QString &category)
{
    RequestMessage request;
    request.setMessage(RequestMessage::RequestType, "GetVideos");
    request.setMessage(RequestMessage::VideoCategory, category.toUtf8());
    request.commit();

    // 包含有中文，需要转码
    QString str = QString::fromUtf8(request.data());
    m_socket->write(str.toLocal8Bit());
}

void VideoModel::closeSocket()
{
    m_socket->close();
}

void VideoModel::responseData()
{
    QString response = QString::fromLocal8Bit(m_socket->readAll());

    QXmlStreamReader xml(response);
    if(xml.readNextStartElement())
    {
        if(xml.name().toString() == "ThinkThink") // 确保是ThinkThink消息
        {
            while(xml.readNextStartElement())
            {
                if(xml.name().toString() == "ResponseType")
                {
                    QString value = xml.readElementText();
                    qDebug() << "response type" << value;
                    if(value == "GetVideos") OnGetVideos(response);
                }
                else
                {
                    xml.skipCurrentElement();
                }
            }
        }
        else
        {
            xml.raiseError(QObject::tr("invalid response message"));
        }
    }
}


void VideoModel::GetUploaderName(const QString &id)
{
    RequestMessage request;
    request.setMessage(RequestMessage::RequestType, "GetUploaderName");
    request.setMessage(RequestMessage::UploaderId, id.toUtf8());
    request.commit();

    m_socket->write(request.data());
}

void VideoModel::OnGetVideos(const QString &response)
{
    QXmlStreamReader xml(response);
    if(xml.readNextStartElement())
    {
        if(xml.name().toString() == "ThinkThink") // 确保是ThinkThink消息
        {
            while(xml.readNextStartElement())
            {
                if(xml.name().toString() == "Video")
                {
                    Video video;
                    QString value;
                    while(xml.readNextStartElement())
                    {
                        if(xml.name().toString() == "Id")
                        {
                            value = xml.readElementText();
                            video.video_id = value;
                        }
                        else if(xml.name().toString() == "Name")
                        {
                            value = xml.readElementText();
                            video.video_name = value;
                        }
                        else if(xml.name().toString() == "Uploader")
                        {
                            value = xml.readElementText();
                            video.uploader = value;
                            GetUploaderName(value);
                        }
                        else if(xml.name().toString() == "CoverImage")
                        {
                            value = xml.readElementText();
                            video.cover_image = value;
                        }
                        else if(xml.name().toString() == "Describe")
                        {
                            value = xml.readElementText();
                            video.describe = value;
                        }
                        else if(xml.name().toString() == "UploadDate")
                        {
                            value = xml.readElementText();
                            video.upload_date = value;
                        }
                        else if(xml.name().toString() == "Source")
                        {
                            value = xml.readElementText();
                            video.source = value;
                        }
                        else
                        {
                            xml.skipCurrentElement();
                        }
                    }
                    addVideo(video);

                }
                else
                {
                    xml.skipCurrentElement();
                }
            }
        }
        else
        {
            xml.raiseError(QObject::tr("invalid response message"));
        }
    }
}

QHash<int, QByteArray> VideoModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[VideoIdRole] = "video_id";
    roles[VideoNameRole] = "video_name";
    roles[UploaderRole] = "uploader";
    roles[CoverImageRole] = "cover_image";
    roles[SourceRole] = "source";
    roles[UploadDateRole] = "upload_date";
    roles[DescribeRole] = "describe";
    return roles;
}


