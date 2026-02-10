#include "checo/qt/tile_table_model.h"
#include "checo/qt/application_info.h"

#include <QDataStream>
#include <QMimeData>
#include <algorithm>

namespace checo::qt
{

const QString TileTableModel::MIME_TYPE = "application/tile.table.model";

TileTableModel::TileTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    connect(&mRunningTilesTimer, &QTimer::timeout, this, &TileTableModel::refreshRunningTiles);
    mRunningTilesTimer.start(5000);
}

TileTableModel::TileTableModel(const std::vector<Tile> &tiles, QObject *parent)
    : TileTableModel(parent)
{
    setTiles(tiles);
    refreshRunningTiles();
}

bool TileTableModel::hasTile(const QModelIndex &index) const
{
    return index.isValid() && modelIndexToContainerIndex(index) < mTiles.size();
}

void TileTableModel::addTile(const Tile &newTile)
{
    beginResetModel();

    mTiles.push_back(newTile);
    refreshRunningTiles();
    calculateDimensions();

    endResetModel();
}

void TileTableModel::removeTile(const QModelIndex &index)
{
    beginResetModel();
    const size_t tileIndex = modelIndexToContainerIndex(index);
    mTiles.erase(mTiles.begin() + tileIndex);
    refreshRunningTiles();
    calculateDimensions();
    endResetModel();
}

void TileTableModel::setTiles(const std::vector<Tile> &tiles)
{
    beginResetModel();

    mTiles = tiles;
    refreshRunningTiles();
    calculateDimensions();

    endResetModel();
}

bool TileTableModel::containsFile(const QFileInfo &file)
{
    return std::find(mTiles.begin(), mTiles.end(), file) != mTiles.end();
}

QModelIndex TileTableModel::index(int row, int column, const QModelIndex &) const
{
    // The last row might be not full
    if (row == mRowCount - 1 && column >= columnCount(row))
        return QModelIndex();

    // For all other rows we can use standard implementation
    return createIndex(row, column);
}

QModelIndex TileTableModel::parent(const QModelIndex &) const
{
    return QModelIndex();
}

int TileTableModel::rowCount(const QModelIndex &) const
{
    return mRowCount;
}

int TileTableModel::rowCount(const int column) const
{
    const int lastRowColumns = columnCount(mRowCount - 1);
    return column < lastRowColumns ? mRowCount : mRowCount - 1;
}

int TileTableModel::columnCount(const QModelIndex &) const
{
    return mColumnCount;
}

int TileTableModel::columnCount(const int row) const
{
    if (row < mRowCount - 1)
        return mColumnCount;
    else
        return static_cast<int>(mTiles.size()) - mColumnCount * (mRowCount - 1);
}

QVariant TileTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const size_t tileIndex = modelIndexToContainerIndex(index);
    if (tileIndex >= mTiles.size())
        return QVariant();
    switch (role)
    {
    case Qt::DisplayRole:
        return mTiles[tileIndex].displayName;
    case Qt::DecorationRole:
        return mTiles[tileIndex].icon;
    case Qt::UserRole:
        return QVariant::fromValue<QFileInfo>(mTiles[tileIndex].file);
    case Qt::UserRole + 1:
        return mRunningTiles[tileIndex];
    default:
        return QVariant();
    }
}

Qt::ItemFlags TileTableModel::flags(const QModelIndex &index) const
{
    const size_t tileIndex = modelIndexToContainerIndex(index);
    if (!index.isValid() || tileIndex >= mTiles.size())
        return Qt::NoItemFlags;

    return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled |
           Qt::ItemNeverHasChildren;
}

Qt::DropActions TileTableModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

QStringList TileTableModel::mimeTypes() const
{
    return QStringList(MIME_TYPE);
}

QMimeData *TileTableModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *result = new QMimeData();
    QByteArray encodedIndexes;
    QDataStream stream(&encodedIndexes, QIODevice::WriteOnly);
    for (const QModelIndex &curIndex : indexes)
        stream << modelIndexToContainerIndex(curIndex);
    result->setData(MIME_TYPE, encodedIndexes);

    return result;
}

bool TileTableModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int, int, const QModelIndex &parent)
{
    // Don't allow drop of unsupported MIME type
    if (!data->hasFormat(MIME_TYPE))
        return false;

    // Don't allow drop with invalid parent
    if (!parent.isValid())
        return false;

    // If we are supposed to ignore drops then we can say that we already did everything
    if (action == Qt::IgnoreAction)
        return true;

    // Get the index of dropped tile
    QByteArray encodedIndex = data->data(MIME_TYPE);
    QDataStream stream(&encodedIndex, QIODevice::ReadOnly);
    size_t dropTileIndex;
    stream >> dropTileIndex;

    // Swap dropped tile with the specified one
    size_t curTileIndex = modelIndexToContainerIndex(parent);
    beginResetModel();
    std::iter_swap(mTiles.begin() + curTileIndex, mTiles.begin() + dropTileIndex);
    endResetModel();

    return true;
}

void TileTableModel::refreshRunningTiles()
{
    // Make sure that we have flag for every tile
    mRunningTiles.resize(mTiles.size());

    // Check which tiles are currently running
    std::list<QFileInfo> runningProcesses = ApplicationInfo::getRunningWindows();
    for (size_t tileIndex = 0; tileIndex < mTiles.size(); ++tileIndex)
    {
        mRunningTiles[tileIndex] = std::find(runningProcesses.begin(), runningProcesses.end(),
                                       mTiles[tileIndex].file) != runningProcesses.end();
    }
}

void TileTableModel::calculateDimensions()
{
    mColumnCount = static_cast<int>(std::ceil(std::sqrt(mTiles.size())));
    if (mTiles.size() <= (std::pow(mColumnCount, 2) - mColumnCount)) // Last row is empty
        mRowCount = mColumnCount - 1;
    else
        mRowCount = mColumnCount;
}

size_t TileTableModel::modelIndexToContainerIndex(const QModelIndex &index) const
{
    return index.row() * mColumnCount + index.column();
}

} // namespace checo::qt::widgets
