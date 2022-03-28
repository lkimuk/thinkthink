#ifndef VIDEOCATEGORYMODEL_H
#define VIDEOCATEGORYMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QTcpSocket>

class VideoController;



class VideoCategoryModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum VideoCategoryRoles {
        NameRole = Qt::UserRole + 1
    };
    VideoCategoryModel(QObject *parent = nullptr);

    void addCategory(const QString& categoryName);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    QString at(int index) const;

    void setVideoController(VideoController* controller);

protected:
    QHash<int, QByteArray> roleNames() const;

signals:
    void categoryChanged();

private slots:
    void requestCategories();
    void responseData();
    void closeSocket();
    void updateVideos();

private:
    QList<QString> m_categories;
    QTcpSocket* m_socket;
    VideoController* m_videoController;
};

#endif // VIDEOCATEGORYMODEL_H
