#pragma once

#include "checo/ui/overlay_dialog.h"
#include "checo_dialogs_export.h"

#include <QSortFilterProxyModel>

namespace Ui
{
class SelectListItemDialog;
}

namespace checo::ui
{

/// Dialog to select item in the list model
class CHECO_DIALOGS_EXPORT SelectListItemDialog : public OverlayDialog
{
    Q_OBJECT

  public:
    explicit SelectListItemDialog(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    ~SelectListItemDialog() override;

  public:
    /// Set \p model which should be displayed in the dialog
    virtual void setModel(QAbstractItemModel *model);

    /// Get model index for the selected item
    QModelIndex selectedIndex() const;

  public:
    QSize sizeHint() const override;

  signals:
    void selectNotListedClicked();

  protected:
    void showEvent(QShowEvent *event) override;

  private slots:
    /// Update the item counter displayed to the user
    void refreshItemCount();

  private:
    /// User Interface for this dialog
    Ui::SelectListItemDialog *mUi = nullptr;
    /// Model that provides sorting and filtering of data
    QSortFilterProxyModel *mModel = nullptr;
};

} // namespace checo::ui
