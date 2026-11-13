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

#include "checo/qt/text_edit_dialog.h"
#include "ui_text_edit_dialog.h"

namespace checo::qt
{

TextEditDialog::TextEditDialog(QWidget *parent, Qt::WindowFlags flags)
    : OverlayDialog(parent, flags),
      mUi(new Ui::TextEditDialog)
{
    mUi->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlag(Qt::NoDropShadowWindowHint);

    // Make background of this widget transparent (WARNING: Works with Qt::FramelessWindowHint only)
    setAttribute(Qt::WA_TranslucentBackground);

    // Configure buttons visualization
    mUi->btnOk->setStateIcon(QStyle::State_Enabled, QIcon::fromTheme("tick"));
    mUi->btnOk->setStateIcon(QStyle::State_MouseOver, QIcon::fromTheme("tick_mouseover"));
    mUi->btnCancel->setStateIcon(QStyle::State_MouseOver, QIcon::fromTheme("cancel_mouseover"));

    // Enable OK button only when there is some text entered
    mUi->btnOk->setEnabled(false);
    connect(mUi->edtText, &QPlainTextEdit::textChanged, this,
        [&]() { mUi->btnOk->setEnabled(!mUi->edtText->toPlainText().isEmpty()); });

    // Initially focus the editor to reduce the number of clicks required from the user
    mUi->edtText->setFocus();

    // Accept/reject dialog on button clicks
    connect(mUi->btnOk, &MultiIconButton::clicked, this, &OverlayDialog::accept);
    connect(mUi->btnCancel, &MultiIconButton::clicked, this, &OverlayDialog::reject);
}

TextEditDialog::~TextEditDialog()
{
    delete mUi;
}

QString TextEditDialog::text() const
{
    return mUi->edtText->toPlainText();
}

void TextEditDialog::setText(const QString &newText)
{
    mUi->edtText->setPlainText(newText);
}

} // namespace checo::qt
