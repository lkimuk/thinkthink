#ifndef VIDEOMODEL_H
#define VIDEOMODEL_H

#include <QAbstractListModel>
#include <QStringList>


class QTcpSocket;


struct Video {
    QString video_id;
    QString video_name;
    QString uploader;
    QString cover_image;
    QString source;
    QString upload_date;
    QString describe;
};


class VideoModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum VideoRoles {
        VideoNameRole = Qt::UserRole + 1,
        UploaderRole,
        UploadDateRole,
        CoverImageRole,
        DescribeRole,
        VideoIdRole,
        SourceRole
    };
    explicit VideoModel(QObject *parent = nullptr);

    // 添加视频到Model中
    void addVideo(const Video& video);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    // 从服务器获取视频列表
    void updateVideos(const QString& category);

private slots:
    void closeSocket();
    void responseData();

private:
    // 要据上传者ID，获取名称
    void GetUploaderName(const QString& id);
    void OnGetVideos(const QString& response);


protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<Video> m_videos;
    QTcpSocket* m_socket;
};

#endif // VIDEOMODEL_H
