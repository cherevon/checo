#include "checo/ui/tile_view.h"
#include "checo/ui/tile_table_model.h"

#include <QDrag>
#include <QHeaderView>
#include <QMouseEvent>
#include <QPainter>

namespace checo::ui
{

TileView::TileView(QWidget *parent) : QTableView(parent)
{
    // Create the button to delete tiles
    mDeleteTileButton = new MultiIconButton(this);
    mDeleteTileButton->setIcon(QIcon::fromTheme("delete_tile"));
    mDeleteTileButton->setStateIcon(QStyle::State_MouseOver, QIcon::fromTheme("delete_tile_mouseover"));
    mDeleteTileButton->setFlat(true);
    mDeleteTileButton->setVisible(false);
    connect(mDeleteTileButton, &MultiIconButton::clicked, this,
        [this]
        {
            TileTableModel *tileModel = dynamic_cast<TileTableModel *>(model());
            if (tileModel)
            {
                tileModel->removeTile(mDeleteButtonIndex);
                hideDeleteTileButton();
            }
        });
}

void TileView::updateGeometries()
{
    QTableView::updateGeometries();

    // Resize the button to delete tiles so that it takes 1/6 of a single tile height
    const int iconHeight = verticalHeader()->sectionSize(0) / 6;
    mDeleteTileButton->setIconSize(QSize(iconHeight, iconHeight));
    mDeleteTileButton->resize(mDeleteTileButton->iconSize());

    // Position the button to delete tiles in the correct tile
    moveDeleteTileButton(mDeleteButtonIndex);
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
    // Nothing to drag if we don't have any selected index
    if (selectedIndexes().empty())
        return;

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
    mIsDragging = true;
    drag.exec(supportedActions);
    mIsDragging = false;
}

void TileView::mousePressEvent(QMouseEvent *event)
{
    // Show/hide button to delete tile on right click
    const QModelIndex tileIndex = indexAt(event->pos());
    if (event->button() == Qt::RightButton && (tileIndex != mDeleteButtonIndex))
        showDeleteTileButton(tileIndex);
    else
        hideDeleteTileButton();

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
        return;

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
    mDeleteButtonIndex = index;
    moveDeleteTileButton(mDeleteButtonIndex);
    mDeleteTileButton->show();
}

void TileView::hideDeleteTileButton()
{
    mDeleteButtonIndex = QModelIndex();
    mDeleteTileButton->hide();
}

void TileView::moveDeleteTileButton(const QModelIndex &index)
{
    // Nothing to do if the model index is invalid
    if (!index.isValid())
        return;

    // Position the button to delete tiles in top right corner of the tile
    const QRect tileRect = visualRect(index);
    const int delButtonX = tileRect.right() - mDeleteTileButton->iconSize().width() - tileRect.height() / 15;
    mDeleteTileButton->move(delButtonX, tileRect.top() + tileRect.height() / 15);
}

} // namespace checo::ui
