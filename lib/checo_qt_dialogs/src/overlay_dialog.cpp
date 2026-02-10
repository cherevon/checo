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
