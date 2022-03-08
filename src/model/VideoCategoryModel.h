#ifndef VIDEOCATEGORYMODEL_H
#define VIDEOCATEGORYMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QTcpSocket>



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

protected:
    QHash<int, QByteArray> roleNames() const;

private slots:
    void requestCategories();
    void responseData();
    void closeSocket();

private:
    QList<QString> m_categories;
    QTcpSocket* m_socket;
};

#endif // VIDEOCATEGORYMODEL_H
