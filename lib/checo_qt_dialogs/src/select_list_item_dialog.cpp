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

#include "checo/qt/select_list_item_dialog.h"
#include "ui_select_list_item_dialog.h"

#include <QScrollBar>
#include <QScroller>

namespace checo::qt
{

SelectListItemDialog::SelectListItemDialog(QWidget *parent, Qt::WindowFlags flags)
    : OverlayDialog(parent, flags),
      mUi(new Ui::SelectListItemDialog)
{
    mUi->setupUi(this);
    mUi->listView->setVerticalScrollBar(new QScrollBar(mUi->listView));

    // Allow scrolling the view with the touchscreen
    QScroller::grabGesture(mUi->listView->viewport(), QScroller::TouchGesture);

    // Create model
    mModel = new QSortFilterProxyModel(mUi->listView);
    mModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    mModel->setSortRole(Qt::DisplayRole);
    mModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    mModel->sort(0);
    mUi->listView->setModel(mModel);

    // Make the total number of items always up to date
    connect(mModel, &QAbstractItemModel::modelReset, this, &SelectListItemDialog::refreshItemCount);
    connect(mModel, &QAbstractItemModel::rowsInserted, this, &SelectListItemDialog::refreshItemCount);
    connect(mModel, &QAbstractItemModel::rowsRemoved, this, &SelectListItemDialog::refreshItemCount);

    // Update filter when the user types something in the search line edit
    connect(mUi->edtFilter, &QLineEdit::textChanged, mModel, &QSortFilterProxyModel::setFilterFixedString);

    // When the user selects some item the dialog should be accepted
    connect(mUi->listView, &QListView::clicked, this, &SelectListItemDialog::accept);

    // Forward signal to support custom handlers for selecting items which are not present in the list
    connect(mUi->btnSelectNotFromList, &QPushButton::clicked, this, &SelectListItemDialog::selectNotListedClicked);
}

void SelectListItemDialog::setModel(QAbstractItemModel *model)
{
    mModel->setSourceModel(model);
}

QModelIndex SelectListItemDialog::selectedIndex() const
{
    return mModel->mapToSource(mUi->listView->currentIndex());
}

SelectListItemDialog::~SelectListItemDialog()
{
    delete mUi;
}

QSize SelectListItemDialog::sizeHint() const
{
    return QSize(mUi->listView->sizeHintForColumn(0) + mUi->listView->verticalScrollBar()->width(),
        OverlayDialog::sizeHint().height());
}

void SelectListItemDialog::refreshItemCount()
{
    mUi->lblItemCount->setText(tr("%1 item(s)").arg(mModel->rowCount()));
}

void SelectListItemDialog::showEvent(QShowEvent *event)
{
    OverlayDialog::showEvent(event);

    mUi->listView->clearSelection();

    mModel->setFilterFixedString("");
    mUi->edtFilter->clear();
    mUi->edtFilter->setFocus();
}

} // namespace checo::qt
