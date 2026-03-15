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

#include "checo/qt/tile.h"
#include "checo_qt_widgets_export.h"

#include <QAbstractTableModel>
#include <QTimer>

namespace checo::qt
{

/// Model that represents tiles in a table
class CHECO_QT_WIDGETS_EXPORT TileTableModel : public QAbstractTableModel
{
    Q_OBJECT

  public:
    explicit TileTableModel(QObject *parent = nullptr);
    explicit TileTableModel(const std::vector<Tile> &tiles, QObject *parent = nullptr);

  public:
    /// Get the total number of tiles
    inline size_t size() const
    {
        return mTiles.size();
    }

    /// Check if the model has tile at \p index
    bool hasTile(const QModelIndex &index) const;

    /// Get tile by its \p index
    inline const Tile &tile(const QModelIndex &index) const
    {
        return mTiles.at(modelIndexToContainerIndex(index));
    }

    /// Get tiles provided by this model
    inline std::vector<Tile> tiles() const
    {
        return mTiles;
    }

    /// Add \p newTile to the model
    void addTile(const Tile &newTile);
    /// Remove the tile at \p index
    void removeTile(const QModelIndex &index);
    /// Set \p tiles provided by the model
    void setTiles(const std::vector<Tile> &tiles);

    /// Check if the model contains tile pointing to the \p file
    bool containsFile(const QFileInfo &file);

  public:
    // Basic functionality:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    /// Get the number of rows in the specified \p column
    int rowCount(const int column) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    /// Get the number of columns in the specified \p row
    int columnCount(const int row) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // Drag & drop support
    Qt::DropActions supportedDropActions() const override;
    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
        const QModelIndex &parent) override;

  private slots:
    /// Refresh running tiles flag
    void refreshRunningTiles();

  private:
    /// Calculate the number of rows and columns provided by this model
    void calculateDimensions();

    /// Convert model index to index of the container in which tiles are stored
    size_t modelIndexToContainerIndex(const QModelIndex &index) const;

  private:
    /// MIME type used for drag & drop
    static const QString MIME_TYPE;

  private:
    /// Tiles provided by the model
    std::vector<Tile> mTiles;
    /// Flag showing if the corresponding tile is running
    std::vector<bool> mRunningTiles;
    /// Timer on timeout of which running tiles are updated
    QTimer mRunningTilesTimer;
    /// Number of rows in the model
    int mRowCount = 0;
    /// Number of columns in the model
    int mColumnCount = 0;
};

} // namespace checo::qt
