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

#include "checo/qt/overlay_dialog.h"

#include <QPainter>
#include <QTimer>

namespace checo::qt
{

void Overlay::paintEvent(QPaintEvent *)
{
    QColor backgroundColor = palette().color(QPalette::Dark);
    backgroundColor.setAlpha(240);
    QPainter(this).fillRect(rect(), backgroundColor);
}

OverlayDialog::OverlayDialog(QWidget *parent, Qt::WindowFlags flags)
    : QDialog(parent, flags)
{
}

OverlayDialog::~OverlayDialog()
{
    if (mOverlay)
        mOverlay->deleteLater();
}

void OverlayDialog::showOverlay()
{
    // Overlay can be shown only in dialog's parent
    QWidget *parentWgt = parentWidget();
    if (!parentWgt)
        return;

    // Show overlay
    if (!mOverlay)
        mOverlay = new Overlay(parentWgt);
    else
        mOverlay->setParent(parentWgt);
    mOverlay->resize(parentWgt->size());
    mOverlay->show();
}

void OverlayDialog::hideOverlay()
{
    // Remove the overlay
    if (mOverlay)
        mOverlay->hide();
}

void OverlayDialog::showEvent(QShowEvent *event)
{
    showOverlay();
    QDialog::showEvent(event);
}

void OverlayDialog::closeEvent(QCloseEvent *event)
{
    // Hide the overlay when all events will be processed (so that mouse clicks won't pass through the overlay widget)
    QTimer::singleShot(0, this, &OverlayDialog::hideOverlay);
    QDialog::closeEvent(event);
}

} // namespace checo::qt
