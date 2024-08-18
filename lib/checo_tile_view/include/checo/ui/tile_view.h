#pragma once

#include "checo/ui/multi_icon_button.h"
#include "checo_tile_view_export.h"

#include <QTableView>

namespace checo::ui
{

/// View that represents tiles in the menu
class CHECO_TILE_VIEW_EXPORT TileView : public QTableView
{
    Q_OBJECT

  public:
    explicit TileView(QWidget *parent = nullptr);

  public:
    /// Check if the user is dragging a tile right now
    inline bool isDragging() const
    {
        return mIsDragging;
    }

  protected slots:
    void updateGeometries() override;

  protected:
    void doPaint(QPaintEvent *event);
    void paintEvent(QPaintEvent *event) override;
    void startDrag(Qt::DropActions supportedActions) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

  private:
    /// Show button to delete tile in the tile with the specified \p index
    void showDeleteTileButton(const QModelIndex &index);
    /// Hide button to delete tile
    void hideDeleteTileButton();
    /// Position the button to delete tile in the tile with the specified \p index
    void moveDeleteTileButton(const QModelIndex &index);

  private:
    /// Index in the model for which the delete button is visible
    QModelIndex mDeleteButtonIndex;
    /// Button which deletes the tile when it is clicked
    MultiIconButton *mDeleteTileButton = nullptr;

    /// Flag representing whether the user is dragging a tile right now
    bool mIsDragging = false;
};

} // namespace checo::ui
