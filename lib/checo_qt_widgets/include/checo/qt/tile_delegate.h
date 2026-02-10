#pragma once

#include "checo_qt_widgets_export.h"

#include <QPushButton>
#include <QStyledItemDelegate>

namespace checo::qt
{

/// Delegate that represents a single tile as a button
class CHECO_QT_WIDGETS_EXPORT TileDelegate : public QStyledItemDelegate
{
  public:
    explicit TileDelegate(QObject *parent = nullptr);

  public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

} // namespace checo::qt
