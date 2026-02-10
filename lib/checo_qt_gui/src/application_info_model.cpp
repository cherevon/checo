#include "checo/qt/application_info_model.h"

namespace checo::qt
{

ApplicationInfoModel::ApplicationInfoModel(const std::vector<ApplicationInfo> &apps, QObject *parent)
    : QAbstractListModel(parent),
      mApps(apps)
{
}

QVariant ApplicationInfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const ApplicationInfo &appItem = mApps.at(index.row());
    switch (role)
    {
    case Qt::DisplayRole:
        return appItem.displayName();
    case Qt::DecorationRole:
        return appItem.normalIcon();
    case Qt::UserRole:
        return appItem.executable().absoluteFilePath();
    default:
        return QVariant();
    }
}

int ApplicationInfoModel::rowCount(const QModelIndex &) const
{
    return static_cast<int>(mApps.size());
}

} // namespace checo::qt
