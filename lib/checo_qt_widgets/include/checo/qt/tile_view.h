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

#include "checo_qt_widgets_export.h"

#include <QAbstractButton>
#include <QTableView>

namespace checo::qt
{

/// View that represents tiles in the form of a table and allows to drag and drop them
class CHECO_QT_WIDGETS_EXPORT TileView : public QTableView
{
    Q_OBJECT

  public:
    explicit TileView(QWidget *parent = nullptr);
    ~TileView() override;

  public:
    /// Check if the user is dragging a tile right now
    inline bool isDragging() const
    {
        return m_IsDragging;
    }

    /// Set custom button to delete tile. This button will be shown when the user hovers a tile and will be hidden when
    /// the user stops hovering it. The button will be automatically positioned on the tile. If the user clicks the
    /// button, the tile will be deleted.
    void setDeleteTileButton(QAbstractButton *deleteTileButton);

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
    /// Resize the button to delete tile to achieve proper size relative to the tile size
    void resizeDeleteTileButton();

  private:
    /// Index in the model for which the delete button is visible
    QModelIndex m_DeleteButtonIndex{};
    /// Button which deletes the tile when it is clicked
    QAbstractButton *m_DeleteTileButton{nullptr};

    /// Flag representing whether the user is dragging a tile right now
    bool m_IsDragging{false};
};

} // namespace checo::qt
