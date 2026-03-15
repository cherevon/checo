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

#include "checo/qt/key_sequence_edit_dialog.h"
#include "ui_key_sequence_edit_dialog.h"

#include <QKeyEvent>

namespace checo::qt
{

KeySequenceEditDialog::KeySequenceEditDialog(QWidget *parent, Qt::WindowFlags flags)
    : OverlayDialog(parent, flags),
      mUi(new Ui::KeySequenceEditDialog)
{
    mUi->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlag(Qt::NoDropShadowWindowHint);

    // Make background of this widget transparent (WARNING: Works with Qt::FramelessWindowHint only)
    setAttribute(Qt::WA_TranslucentBackground);

    initializeEditor();
    initializeButtons();

    // Catch all key events which this application receives
    qApp->installEventFilter(this);
}

KeySequenceEditDialog::~KeySequenceEditDialog()
{
    delete mUi;
}

std::vector<Qt::Key> KeySequenceEditDialog::keys() const
{
    return mKeys;
}

bool KeySequenceEditDialog::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *k = static_cast<QKeyEvent *>(event);
        addKey(static_cast<Qt::Key>(k->key()));
        return true;
    }
    return false;
}

void KeySequenceEditDialog::showEvent(QShowEvent *event)
{
    OverlayDialog::showEvent(event);

    const int iconEdge =
        mUi->edtKeySequence->height() - mUi->btnOk->contentsPadding().top() - mUi->btnOk->contentsPadding().bottom();
    const QSize iconSize(iconEdge, iconEdge);
    mUi->btnOk->setIconSize(iconSize);
    mUi->btnRestart->setIconSize(iconSize);
    mUi->btnCancel->setIconSize(iconSize);
}

void KeySequenceEditDialog::refreshEditor()
{
    QString keysText;
    for (const auto &curKey : mKeys)
    {
        if (!keysText.isEmpty())
        {
            keysText += "+";
        }
        if (curKey == Qt::Key_Meta)
        {
            keysText += "Win";
        }
        else
        {
            keysText += QKeySequence{curKey}.toString();
        }
    }
    mUi->edtKeySequence->setText(keysText);
}

void KeySequenceEditDialog::initializeButtons()
{
    // Configure buttons visualization
    mUi->btnOk->setStateIcon(QStyle::State_Enabled, QIcon::fromTheme("tick"));
    mUi->btnOk->setStateIcon(QStyle::State_MouseOver, QIcon::fromTheme("tick_mouseover"));
    mUi->btnRestart->setStateIcon(QStyle::State_Enabled, QIcon::fromTheme("restart"));
    mUi->btnRestart->setStateIcon(QStyle::State_MouseOver, QIcon::fromTheme("restart_mouseover"));
    mUi->btnCancel->setStateIcon(QStyle::State_MouseOver, QIcon::fromTheme("cancel_mouseover"));

    // Buttons functionality
    connect(mUi->btnOk, &MultiIconButton::clicked, this, &OverlayDialog::accept);
    connect(mUi->btnCancel, &MultiIconButton::clicked, this, &OverlayDialog::reject);
    connect(mUi->btnRestart, &MultiIconButton::clicked, this, &KeySequenceEditDialog::clearKeys);

    // Enable OK and Restart button only when there is some key sequence available
    mUi->btnOk->setEnabled(false);
    mUi->btnRestart->setEnabled(false);
    connect(this, &KeySequenceEditDialog::keysChanged, this,
        [this]
        {
            const bool hasKeys = !mKeys.empty();
            mUi->btnOk->setEnabled(hasKeys);
            mUi->btnRestart->setEnabled(hasKeys);
        });
}

void KeySequenceEditDialog::initializeEditor()
{
    // Initially focus the editor to reduce the number of clicks required from the user
    mUi->edtKeySequence->setFocus();

    // Refresh displayed keys in the editor every time they change
    connect(this, &KeySequenceEditDialog::keysChanged, this, &KeySequenceEditDialog::refreshEditor);
}

void KeySequenceEditDialog::addKey(const Qt::Key newKey)
{
    mKeys.push_back(newKey);
    emit keysChanged();
}

void KeySequenceEditDialog::clearKeys()
{
    mKeys.clear();
    emit keysChanged();
}

} // namespace checo::qt
