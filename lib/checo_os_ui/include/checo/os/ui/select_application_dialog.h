#pragma once

#include "checo/os/application_info.h"
#include "checo/os/application_info_model.h"
#include "checo/ui/select_list_item_dialog.h"
#include "checo_os_ui_export.h"

namespace checo::os::ui
{

/// Dialog to select application from a list of installed applications
class CHECO_OS_UI_EXPORT SelectApplicationDialog : public checo::ui::SelectListItemDialog
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

} // namespace checo::os::ui
