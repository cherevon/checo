#pragma once

#include "checo_tile_view_export.h"

#include <QPushButton>
#include <QStyledItemDelegate>

namespace checo::ui
{

/// Delegate that represents a single tile as a button
class CHECO_TILE_VIEW_EXPORT TileDelegate : public QStyledItemDelegate
{
  public:
    explicit TileDelegate(QObject *parent = nullptr);

  public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

} // namespace checo::ui
