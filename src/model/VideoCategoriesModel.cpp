#include "VideoCategoriesModel.h"

VideoCategoriesModel::VideoCategoriesModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

void VideoCategoriesModel::addCategory(const QString &categoryName)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_categories << categoryName;
    endInsertRows();
}

int VideoCategoriesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_categories.count();
}

QVariant VideoCategoriesModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_categories.count())
        return QVariant();

    if(role == NameRole)
        return m_categories[index.row()];
    return QVariant();
}

QHash<int, QByteArray> VideoCategoriesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}
