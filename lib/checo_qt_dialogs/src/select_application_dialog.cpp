/*
 * MIT License
 *
 * Copyright (c) 2024 Sergei Cherevichko
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
