#include "FileSender.h"
#include "RequestMessage.h"
#include "VideoCategoryModel.h"
#include "VideoController.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>



VideoCategoryModel::VideoCategoryModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_socket = new QTcpSocket();
    connect(m_socket, &QTcpSocket::connected, this, &VideoCategoryModel::requestCategories);
    connect(m_socket, &QTcpSocket::disconnected, this, &VideoCategoryModel::closeSocket);
    connect(m_socket, &QTcpSocket::readyRead, this, &VideoCategoryModel::responseData);
    m_socket->connectToHost("127.0.0.1", 3007);

    connect(this, &VideoCategoryModel::categoryChanged, this, &VideoCategoryModel::updateVideos);
}

void VideoCategoryModel::addCategory(const QString &categoryName)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_categories << categoryName;
    endInsertRows();
}

int VideoCategoryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_categories.count();
}

QVariant VideoCategoryModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_categories.count())
        return QVariant();

    if(role == NameRole)
        return m_categories[index.row()];
    return QVariant();
}

QString VideoCategoryModel::at(int index) const
{
    return m_categories.at(index);
}

void VideoCategoryModel::setVideoController(VideoController *controller)
{
    m_videoController = controller;
}

QHash<int, QByteArray> VideoCategoryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}

void VideoCategoryModel::requestCategories()
{
    qDebug() << "connected to server";

    // request categories from server
    RequestMessage request;
    request.setMessage(RequestMessage::RequestType, "GetVideoCategories");
    request.commit();
    qDebug() << request.data();

    m_socket->write(request.data());
}

void VideoCategoryModel::responseData()
{
    QString data = QString::fromLocal8Bit(m_socket->readAll()); // 转换编码，否则无法解析
    QXmlStreamReader xml(data);
    if(xml.readNextStartElement())
    {
        if(xml.name().toString() == "ThinkThink") // 确保是ThinkThink消息
        {
            while(xml.readNextStartElement())
            {
                if(xml.name().toString() == "Category")
                {
                    QString value = xml.readElementText();
                    // qDebug() << value;
                    addCategory(value);
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

    // 更新视频
    if(m_categories.count() >= 0)
        emit categoryChanged();
}

void VideoCategoryModel::closeSocket()
{
    m_socket->close();
}

void VideoCategoryModel::updateVideos()
{
    QString category = m_categories.at(0);
    m_videoController->updateVideos(category);
}
