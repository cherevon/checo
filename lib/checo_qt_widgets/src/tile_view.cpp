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

#include "checo/qt/tile_view.h"
#include "checo/qt/tile_table_model.h"

#include <QDrag>
#include <QHeaderView>
#include <QMouseEvent>
#include <QPainter>

namespace checo::qt
{

TileView::TileView(QWidget *parent)
    : QTableView(parent)
{
}

TileView::~TileView() = default;

void TileView::setDeleteTileButton(QAbstractButton *deleteTileButton)
{
    // Delete the old button if it exists
    if (m_DeleteTileButton)
    {
        m_DeleteTileButton->deleteLater();
    }

    // Set the new button
    m_DeleteTileButton = deleteTileButton;
    if (!m_DeleteTileButton)
    {
        return;
    }

    // Set the new button properties and add it to the view
    m_DeleteTileButton->setParent(this);
    m_DeleteTileButton->setVisible(false);
    update();

    // Connect the button click to deleting the tile
    connect(m_DeleteTileButton, &QAbstractButton::clicked, this,
        [this]
        {
            TileTableModel *tileModel = dynamic_cast<TileTableModel *>(model());
            if (tileModel)
            {
                tileModel->removeTile(m_DeleteButtonIndex);
                hideDeleteTileButton();
            }
        });
}

void TileView::updateGeometries()
{
    QTableView::updateGeometries();

    if (m_DeleteTileButton)
    {
        // Resize the button to delete tiles
        resizeDeleteTileButton();

        // Position the button to delete tiles in the correct tile
        moveDeleteTileButton(m_DeleteButtonIndex);
    }
}

void TileView::paintEvent(QPaintEvent *event)
{
    // We don't want to draw drop indicator
    setDropIndicatorShown(false);
    QTableView::paintEvent(event);
    setDropIndicatorShown(true);
}

void TileView::startDrag(Qt::DropActions supportedActions)
{
    // Nothing to drag if we don't have any tile selected
    if (selectedIndexes().empty())
    {
        return;
    }

    // Make the image of the item to be dragged
    const QModelIndex dragIndex = selectedIndexes().front();
    const QRect dragItemRect = QRect(QPoint(0, 0), visualRect(dragIndex).size());
    QPixmap dragPixmap(dragItemRect.size());
    dragPixmap.fill(Qt::transparent);
    QPainter painter(&dragPixmap);
    painter.setOpacity(0.5);
    QStyleOptionViewItem styleOption;
    initViewItemOption(&styleOption);
    styleOption.rect = dragItemRect;
    itemDelegate()->paint(&painter, styleOption, dragIndex);
    painter.end();

    // Start dragging the item
    QDrag drag(this);
    drag.setMimeData(model()->mimeData(selectedIndexes()));
    drag.setPixmap(dragPixmap);
    drag.setHotSpot(dragPixmap.rect().center());
    m_IsDragging = true;
    drag.exec(supportedActions);
    m_IsDragging = false;
}

void TileView::mousePressEvent(QMouseEvent *event)
{
    // Show/hide button to delete tile on right click
    const QModelIndex tileIndex = indexAt(event->pos());
    if (event->button() == Qt::RightButton && (tileIndex != m_DeleteButtonIndex))
    {
        showDeleteTileButton(tileIndex);
    }
    else
    {
        hideDeleteTileButton();
    }

    // Keep default behavior like dragging, clicking items too
    QTableView::mousePressEvent(event);
}

void TileView::keyPressEvent(QKeyEvent *event)
{
    const QModelIndex index = currentIndex();

    // Use default keyboard movements
    QTableView::keyPressEvent(event);

    // Advanced keyboard movements are available only for specific tile model
    TileTableModel *tileModel = dynamic_cast<TileTableModel *>(model());
    if (!tileModel)
    {
        return;
    }

    // Advanced movements for the view
    int newRow = currentIndex().row();
    int newColumn = currentIndex().column();
    switch (event->key())
    {
    case Qt::Key_Left:
        if (index.column() == 0)
        {
            newRow = index.row() == 0 ? tileModel->rowCount() - 1 : index.row() - 1;
            newColumn = tileModel->columnCount(newRow) - 1;
        }
        break;
    case Qt::Key_Right:
        if (index.column() == tileModel->columnCount(index.row()) - 1)
        {
            newRow = index.row() == tileModel->rowCount() - 1 ? 0 : newRow + 1;
            newColumn = 0;
        }
        break;
    case Qt::Key_Up:
        if (index.row() == 0)
        {
            newColumn = index.column() == 0 ? tileModel->columnCount() - 1 : index.column() - 1;
            newRow = tileModel->rowCount(newColumn) - 1;
        }
        break;
    case Qt::Key_Down:
        if (index.row() == tileModel->rowCount(index.column()) - 1)
        {
            newColumn = index.column() == tileModel->columnCount() - 1 ? 0 : index.column() + 1;
            newRow = 0;
        }
        break;
    }

    QModelIndex newIndex = tileModel->index(newRow, newColumn);
    setCurrentIndex(newIndex);
}

void TileView::showDeleteTileButton(const QModelIndex &index)
{
    m_DeleteButtonIndex = index;
    moveDeleteTileButton(m_DeleteButtonIndex);
    m_DeleteTileButton->show();
}

void TileView::hideDeleteTileButton()
{
    m_DeleteButtonIndex = QModelIndex();
    m_DeleteTileButton->hide();
}

void TileView::moveDeleteTileButton(const QModelIndex &index)
{
    // Nothing to do if the model index is invalid
    if (!index.isValid())
    {
        return;
    }

    // Position the button to delete tiles in top right corner of the tile
    const QRect tileRect = visualRect(index);
    const int delButtonX = tileRect.right() - m_DeleteTileButton->iconSize().width() - tileRect.height() / 15;
    m_DeleteTileButton->move(delButtonX, tileRect.top() + tileRect.height() / 15);
}

void TileView::resizeDeleteTileButton()
{
    // Nothing to do if we don't have the button
    if (!m_DeleteTileButton)
    {
        return;
    }

    // Resize the button to delete tiles so that it takes 1/6 of a single tile height
    const int iconHeight = verticalHeader()->sectionSize(0) / 6;
    m_DeleteTileButton->setIconSize(QSize(iconHeight, iconHeight));
    m_DeleteTileButton->resize(m_DeleteTileButton->iconSize());
}

} // namespace checo::qt
