#pragma once

#include "checo/ui/overlay_dialog.h"
#include "checo_dialogs_export.h"

namespace Ui
{
class KeySequenceEditDialog;
}

namespace checo::ui
{

/// This dialog allows the user to edit key sequence
class CHECO_DIALOGS_EXPORT KeySequenceEditDialog : public OverlayDialog
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

} // namespace checo::ui
