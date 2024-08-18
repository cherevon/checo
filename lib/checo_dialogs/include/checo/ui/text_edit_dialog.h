#pragma once

#include "checo/ui/overlay_dialog.h"
#include "checo_dialogs_export.h"

namespace Ui
{
class TextEditDialog;
}

namespace checo::ui
{

/// This dialog allows the user to edit multiline text
class CHECO_DIALOGS_EXPORT TextEditDialog : public OverlayDialog
{
    Q_OBJECT

  public:
    explicit TextEditDialog(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    ~TextEditDialog() override;

    QString text() const;
    void setText(const QString &newText);

  private:
    Ui::TextEditDialog *mUi{nullptr};
};

} // namespace checo::ui
