#pragma once

#include "checo/qt/command_executor.h"
#include "checo_qt_command_executor_export.h"

namespace checo::qt
{

/// Command which types text when executed
class CHECO_QT_COMMAND_EXECUTOR_EXPORT TypeTextCommandExecutor : public CommandExecutor
{
  public:
    TypeTextCommandExecutor();
    explicit TypeTextCommandExecutor(const QString &text);

    ~TypeTextCommandExecutor() override;

  public:
    void execute() override;

    QByteArray toByteArray() const override;
    void fromByteArray(const QByteArray &data) override;

    QString toString() override;

    const QString &text() const
    {
        return m_Text;
    }

    void setText(const QString &newText)
    {
        m_Text = newText;
    }

  private:
    /// Text to type when the command is executed
    QString m_Text{};
};

} // namespace checo::qt
