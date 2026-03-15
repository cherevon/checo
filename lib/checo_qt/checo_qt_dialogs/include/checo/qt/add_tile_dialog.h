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
