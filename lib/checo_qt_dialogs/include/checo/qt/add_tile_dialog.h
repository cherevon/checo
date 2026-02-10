#pragma once

#include "checo/qt/multi_icon_button.h"
#include "checo/qt/overlay_dialog.h"
#include "checo/qt/tile.h"
#include "checo_qt_dialogs_export.h"

namespace Ui
{
class AddTileDialog;
}

namespace checo::qt
{

/// Dialog to select a new tile
class CHECO_QT_DIALOGS_EXPORT AddTileDialog : public OverlayDialog
{
    Q_OBJECT

  public:
    explicit AddTileDialog(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    ~AddTileDialog() override;

  public:
    /// Get the tile selected in this dialog
    inline const Tile &selectedTile() const
    {
        return mSelectedTile;
    }

  public:
    QSize sizeHint() const override;

    /// Set spacing between buttons
    void setButtonSpacing(const int spacing);

  private slots:
    /// Select file on disk from the dialog
    void selectFile();
    /// Select directory on disk from the dialog
    void selectDirectory();
    /// Select application from the dialog
    void selectApplication();

  private:
    /// Get all buttons in this dialog
    std::vector<MultiIconButton *> buttons() const;

  private:
    /// UI of this dialog
    Ui::AddTileDialog *mUi = nullptr;
    /// Tile selected in this dialog
    Tile mSelectedTile;
};

} // namespace checo::qt
