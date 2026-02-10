#include "checo/qt/tile_delegate.h"
#include "checo/qt/tile_view.h"

#include <QApplication>
#include <QPainter>
#include <QStyle>

namespace checo::qt
{

TileDelegate::TileDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void TileDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // Get palette to be used
    QPalette palette = qApp->palette();

    const QVariant displayRoleData = index.model()->data(index, Qt::DisplayRole);
    if (displayRoleData.isValid())
    {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);

        // Calulate margins for the tile
        const bool isSelected = option.state.testFlag(QStyle::State_Selected);
        int margin = isSelected ? 0 : option.rect.width() * 0.007;

        // When the user is dragging some tile right now then drop-target tile becomes even smaller
        const bool isMouseOver = option.state.testFlag(QStyle::State_MouseOver);
        TileView *view = dynamic_cast<TileView *>(parent());
        if (isMouseOver && !isSelected && view && view->isDragging())
            margin = option.rect.width() * 0.05;

        // Draw background rectangle of the tile
        const QRect tileRect = option.rect.adjusted(margin, margin, -margin, -margin);
        if (isSelected)
            painter->fillRect(tileRect, palette.mid());
        else
            painter->fillRect(tileRect, palette.button());

        // Draw icon in the center of the rectangle
        const QIcon icon = index.model()->data(index, Qt::DecorationRole).value<QIcon>();
        const int iconHeight = tileRect.height() * 0.4; // Icon takes 40% of the tile height
        const QRect iconRect(tileRect.center() - QPoint(iconHeight / 2, iconHeight / 2), QSize(iconHeight, iconHeight));
        const QImage iconPixmap = icon.pixmap(iconHeight).toImage();
        painter->drawImage(iconRect, iconPixmap);

        // Draw tile text under icon
        QFont textFont = option.font;
        textFont.setPixelSize(iconHeight * 0.2); // Text takes 20% of the icon height
        painter->setFont(textFont);
        const QFontMetrics textMetrics(textFont);
        const QPoint textTopLeft(tileRect.x() + textMetrics.averageCharWidth(), iconRect.bottom());
        const QRect textRect = QRect(textTopLeft, QSize(tileRect.width() - textMetrics.averageCharWidth() * 2,
                                                      textMetrics.boundingRect(displayRoleData.toString()).height()));
        const QString textToDraw = textMetrics.elidedText(displayRoleData.toString(), Qt::ElideRight, textRect.width());
        painter->setPen(palette.color(QPalette::ButtonText));
        painter->drawText(textRect, Qt::AlignCenter, textToDraw);

        // Draw colored box representing running tile under the tile text
        const bool isTileRunning = index.model()->data(index, Qt::UserRole + 1).toBool();
        if (isTileRunning)
        {
            const QSize runBoxSize(tileRect.width() / 2, textRect.height() / 2);
            const QRect runBoxRect(
                QPoint(tileRect.x() + runBoxSize.width() / 2, textRect.bottom() + textRect.height() / 2), runBoxSize);
            painter->fillRect(runBoxRect, palette.highlight());
        }

        painter->restore();
    }
}

} // namespace checo::qt::widgets
