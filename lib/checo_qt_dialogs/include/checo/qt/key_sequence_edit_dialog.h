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

#include "checo/qt/overlay_dialog.h"
#include "checo_qt_dialogs_export.h"

namespace Ui
{
class KeySequenceEditDialog;
}

namespace checo::qt
{

/// This dialog allows the user to edit key sequence
class CHECO_QT_DIALOGS_EXPORT KeySequenceEditDialog : public OverlayDialog
{
    Q_OBJECT

  public:
    explicit KeySequenceEditDialog(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    ~KeySequenceEditDialog() override;

    std::vector<Qt::Key> keys() const;

  signals:
    void keysChanged();

  protected:
    bool eventFilter(QObject *, QEvent *event) override;
    void showEvent(QShowEvent *event) override;

  private slots:
    void clearKeys();
    void refreshEditor();

  private:
    void initializeButtons();
    void initializeEditor();

    void addKey(const Qt::Key newKey);

  private:
    Ui::KeySequenceEditDialog *mUi{nullptr};
    std::vector<Qt::Key> mKeys;
};

} // namespace checo::qt
