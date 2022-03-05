#include "VideoCategoryModel.h"

VideoCategoryModel::VideoCategoryModel(QObject *parent)
    : QAbstractListModel{parent}
{
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

QHash<int, QByteArray> VideoCategoryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}
