#pragma once

#include "checo/qt/application_info.h"
#include "checo/qt/application_info_model.h"
#include "checo/qt/select_list_item_dialog.h"
#include "checo_qt_dialogs_export.h"

namespace checo::qt
{

/// Dialog to select application from a list of installed applications
class CHECO_QT_DIALOGS_EXPORT SelectApplicationDialog : public SelectListItemDialog
{
    Q_OBJECT

  public:
    explicit SelectApplicationDialog(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

  public:
    const ApplicationInfo &selectedApplication() const;

  public slots:
    void selectApplicationWithFileDialog();

  private:
    static ApplicationInfoModel *mModel;
    std::shared_ptr<ApplicationInfo> mSelectedNotListedApp;
};

} // namespace checo::qt
