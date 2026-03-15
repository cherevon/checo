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

#include "checo/qt/add_tile_dialog.h"
#include "checo/qt/select_application_dialog.h"
#include "ui_add_tile_dialog.h"

#include <QFileDialog>

namespace checo::qt
{

AddTileDialog::AddTileDialog(QWidget *parent, Qt::WindowFlags flags)
    : OverlayDialog(parent, flags),
      mUi(new Ui::AddTileDialog)
{
    mUi->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlag(Qt::NoDropShadowWindowHint);

    // Make background of this widget transparent (WARNING: Works with Qt::FramelessWindowHint only)
    setAttribute(Qt::WA_TranslucentBackground);

    // Configure buttons visualization
    mUi->btnSelectFile->setStateIcon(QStyle::State_MouseOver, QIcon::fromTheme("file_mouseover"));
    mUi->btnSelectDirectory->setStateIcon(QStyle::State_MouseOver, QIcon::fromTheme("directory_mouseover"));
    mUi->btnSelectApplication->setStateIcon(QStyle::State_MouseOver, QIcon::fromTheme("application_mouseover"));

    const int charHeight = fontMetrics().height();
    const QMargins buttonPadding = QMargins(charHeight, charHeight, charHeight, charHeight);
    for (MultiIconButton *btn : buttons())
    {
        btn->setButtonStyle(MultiIconButton::TextUnderIcon);
        btn->setContentsPadding(buttonPadding);
    }

    // Call corresponding slots when buttons are clicked
    connect(mUi->btnSelectFile, &MultiIconButton::clicked, this, &AddTileDialog::selectFile);
    connect(mUi->btnSelectDirectory, &MultiIconButton::clicked, this, &AddTileDialog::selectDirectory);
    connect(mUi->btnSelectApplication, &MultiIconButton::clicked, this, &AddTileDialog::selectApplication);
}

AddTileDialog::~AddTileDialog()
{
    delete mUi;
}

QSize AddTileDialog::sizeHint() const
{
    // Get dimensions of the largest button
    int maxHeight = 0;
    int maxWidth = 0;
    const std::vector<MultiIconButton *> dialogButtons = buttons();
    for (MultiIconButton *btn : dialogButtons)
    {
        QSize btnSize = btn->sizeHint();
        maxWidth = std::max(maxWidth, btnSize.width());
        maxHeight = std::max(maxHeight, btnSize.height());
    }

    // Calculate the most appropriate size for the dialog
    const int btnCount = static_cast<int>(dialogButtons.size());
    return QSize(maxWidth * btnCount + mUi->horizontalLayout->spacing() * (btnCount - 1), maxHeight);
}

void AddTileDialog::setButtonSpacing(const int spacing)
{
    mUi->horizontalLayout->setSpacing(spacing);
}

void AddTileDialog::selectFile()
{
    const QString fileName = QFileDialog::getOpenFileName(nullptr);
    if (fileName.isEmpty())
    {
        reject();
        return;
    }

    const QFileInfo selectedFile = QFileInfo(fileName);
    mSelectedTile = Tile(Tile::File, selectedFile.completeBaseName(), selectedFile);
    accept();
}

void AddTileDialog::selectDirectory()
{
    const QString dirName = QFileDialog::getExistingDirectory(nullptr);
    if (dirName.isEmpty())
    {
        reject();
        return;
    }

    const QFileInfo selectedDir = QFileInfo(dirName);
    mSelectedTile = Tile(Tile::File, selectedDir.fileName(), selectedDir);
    accept();
}

void AddTileDialog::selectApplication()
{
    SelectApplicationDialog dialogSelectApp(parentWidget(), Qt::Popup);
    dialogSelectApp.setFont(font());
    if (parentWidget())
    {
        dialogSelectApp.resize(dialogSelectApp.sizeHint().width(), parentWidget()->height() * 5 / 6);
    }

    if (dialogSelectApp.exec())
    {
        const ApplicationInfo &selectedApp = dialogSelectApp.selectedApplication();
        mSelectedTile = Tile(Tile::Executable, selectedApp.displayName(), selectedApp.executable());
        accept();
    }
    else
    {
        reject();
    }
}

std::vector<MultiIconButton *> AddTileDialog::buttons() const
{
    return {mUi->btnSelectFile, mUi->btnSelectDirectory, mUi->btnSelectApplication};
}

} // namespace checo::qt
