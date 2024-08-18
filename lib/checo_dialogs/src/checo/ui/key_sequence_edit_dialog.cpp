#include "checo/ui/key_sequence_edit_dialog.h"
#include "ui_key_sequence_edit_dialog.h"

#include <QKeyEvent>

namespace checo::ui
{

KeySequenceEditDialog::KeySequenceEditDialog(QWidget *parent, Qt::WindowFlags flags)
    : OverlayDialog(parent, flags), mUi(new Ui::KeySequenceEditDialog)
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

} // namespace checo::ui
