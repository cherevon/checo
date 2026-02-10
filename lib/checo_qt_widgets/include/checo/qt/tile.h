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
