#include "checo/ui/text_edit_dialog.h"
#include "ui_text_edit_dialog.h"

namespace checo::ui
{

TextEditDialog::TextEditDialog(QWidget *parent, Qt::WindowFlags flags)
    : OverlayDialog(parent, flags), mUi(new Ui::TextEditDialog)
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

} // namespace checo::ui
