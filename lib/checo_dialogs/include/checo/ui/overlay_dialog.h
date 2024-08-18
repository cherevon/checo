#pragma once

#include "checo_dialogs_export.h"

#include <QDialog>

namespace checo::ui
{

/// Widget that implements background darkening
class CHECO_DIALOGS_EXPORT Overlay : public QWidget
{
    Q_OBJECT

  public:
    explicit Overlay(QWidget *parent = nullptr) : QWidget(parent)
    {
    }

  protected:
    void paintEvent(QPaintEvent *event) override;
};

/// Dialog that displays dark overlay behind it
class CHECO_DIALOGS_EXPORT OverlayDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit OverlayDialog(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    ~OverlayDialog() override;

  public slots:
    /// Show dark background behind the dialog
    void showOverlay();
    /// Hide dark background behind the dialog
    void hideOverlay();

  protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

  private:
    /// Dark background behind the dialog
    Overlay *mOverlay = nullptr;
};

} // namespace checo::ui
