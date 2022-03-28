#ifndef VIDEOMODEL_H
#define VIDEOMODEL_H

#include <QAbstractListModel>
#include <QStringList>


class QTcpSocket;


class Video {
public:
    Video(const QString& title, const QString& uploader, const QString& upload_date);

    QString title() const;
    QString uploader() const;
    QString upload_date() const;

private:
    QString m_title;
    QString m_uploader;
    QString m_uploadDate;
};


class VideoModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum VideoRoles {
        TitleRole = Qt::UserRole + 1,
        UploaderRole,
        UploadDateRole
    };
    explicit VideoModel(QObject *parent = nullptr);

    void addVideo(const Video& video);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    void updateVideos(const QString& category);

private slots:
    void closeSocket();
    void responseData();


protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<Video> m_videos;
    QTcpSocket* m_socket;
};

#endif // VIDEOMODEL_H
