#ifndef VIDEOCATEGORIESMODEL_H
#define VIDEOCATEGORIESMODEL_H

#include <QAbstractListModel>
#include <QStringList>



class VideoCategoriesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum VideoCategoryRoles {
        NameRole = Qt::UserRole + 1
    };
    VideoCategoriesModel(QObject *parent = nullptr);

    void addCategory(const QString& categoryName);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<QString> m_categories;
};

#endif // VIDEOCATEGORIESMODEL_H
