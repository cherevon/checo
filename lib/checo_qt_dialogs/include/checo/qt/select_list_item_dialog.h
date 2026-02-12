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

#pragma once

#include "checo/qt/overlay_dialog.h"
#include "checo_qt_dialogs_export.h"

#include <QSortFilterProxyModel>

namespace Ui
{
class SelectListItemDialog;
}

namespace checo::qt
{

/// Dialog to select item in the list model
class CHECO_QT_DIALOGS_EXPORT SelectListItemDialog : public OverlayDialog
{
    Q_OBJECT

  public:
    explicit SelectListItemDialog(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    ~SelectListItemDialog() override;

  public:
    /// Set \p model which should be displayed in the dialog
    virtual void setModel(QAbstractItemModel *model);

    /// Get model index for the selected item
    QModelIndex selectedIndex() const;

  public:
    QSize sizeHint() const override;

  signals:
    void selectNotListedClicked();

  protected:
    void showEvent(QShowEvent *event) override;

  private slots:
    /// Update the item counter displayed to the user
    void refreshItemCount();

  private:
    /// User Interface for this dialog
    Ui::SelectListItemDialog *mUi = nullptr;
    /// Model that provides sorting and filtering of data
    QSortFilterProxyModel *mModel = nullptr;
};

} // namespace checo::qt
