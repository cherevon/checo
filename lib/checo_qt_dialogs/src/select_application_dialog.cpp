#include "checo/qt/select_application_dialog.h"

#include <QFileDialog>

namespace checo::qt
{

ApplicationInfoModel *SelectApplicationDialog::mModel = nullptr;

SelectApplicationDialog::SelectApplicationDialog(QWidget *parent, Qt::WindowFlags flags)
    : SelectListItemDialog(parent, flags)
{
    if (!mModel)
        mModel = new ApplicationInfoModel(ApplicationInfo::installedApplications());
    setModel(mModel);

    // Select application from the file when the user clicks button to find not listed applications
    connect(this, &SelectApplicationDialog::selectNotListedClicked, this,
        &SelectApplicationDialog::selectApplicationWithFileDialog);
}

const ApplicationInfo &SelectApplicationDialog::selectedApplication() const
{
    if (mSelectedNotListedApp)
    {
        return *mSelectedNotListedApp;
    }
    else
    {
        return mModel->application(selectedIndex());
    }
}

void SelectApplicationDialog::selectApplicationWithFileDialog()
{
    const QFileInfo executable{QFileDialog::getOpenFileName(parentWidget(), tr("Select application executable"))};
    if (executable.exists())
    {
        mSelectedNotListedApp = std::make_shared<ApplicationInfo>(executable.baseName(), executable);
        accept();
    }
}

} // namespace checo::qt
