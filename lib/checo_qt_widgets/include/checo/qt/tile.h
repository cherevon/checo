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

#include "checo/qt/application_info.h"
#include "checo_qt_widgets_export.h"

#include <QFileInfo>
#include <QIcon>

namespace checo::qt
{

/// Information about a single tile displayed in the menu
struct CHECO_QT_WIDGETS_EXPORT Tile
{
    /// Type of the tile
    enum TileType
    {
        File,       ///< File on disk
        Directory,  ///< Directory on disk
        Executable, ///< Executable file on disk
    };

    Tile() = default;

    Tile(const TileType inType, const QString &inName, const QFileInfo &inFile)
        : type(inType),
          displayName(inName),
          file(inFile)
    {
        loadIcon();
    }

    /// Check if this tile is pointing to \p anotherFile
    bool operator==(const QFileInfo &anotherFile) const
    {
        return file == anotherFile;
    }

    /// Load icon for this tile
    void loadIcon()
    {
        icon = ApplicationInfo::getAssociatedIcon(file, QSize(256, 256));
        if (icon.isNull())
        {
            switch (type)
            {
            case Tile::File:
                icon = QIcon::fromTheme("file");
                break;
            case Tile::Directory:
                icon = QIcon::fromTheme("directory");
                break;
            case Tile::Executable:
                icon = QIcon::fromTheme("application");
                break;
            }
        }
    }

    /// Type of the tile
    TileType type;
    /// Name of the tile that should be visible to the user
    QString displayName;
    /// File that should be opened/executed
    QFileInfo file;
    /// Icon representing the tile
    QIcon icon;
};

} // namespace checo::qt
