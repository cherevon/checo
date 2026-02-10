#pragma once

#include "checo/qt/application_info.h"
#include "checo_qt_gui_export.h"

#include <QAbstractListModel>

#include <vector>

namespace checo::qt
{

/// Model that provides a list of applications
class CHECO_QT_GUI_EXPORT ApplicationInfoModel : public QAbstractListModel
{
    Q_OBJECT

  public:
    explicit ApplicationInfoModel(const std::vector<ApplicationInfo> &apps, QObject *parent = nullptr);
    virtual ~ApplicationInfoModel() = default;

  public:
    /// Get the application by its \p index
    inline const ApplicationInfo &application(const QModelIndex &index)
    {
        return mApps[index.row()];
    }

  public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

  private:
    /// The list of all applications
    std::vector<ApplicationInfo> mApps;
};

} // namespace checo::qt
