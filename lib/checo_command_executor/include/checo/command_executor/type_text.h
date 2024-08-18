#pragma once

#include "checo/command_executor/command_executor.h"

namespace checo::command_executor
{

/// Command which types text when executed
class CHECO_COMMAND_EXECUTOR_EXPORT TypeTextCommandExecutor : public CommandExecutor
{
  public:
    TypeTextCommandExecutor() = default;
    explicit TypeTextCommandExecutor(const QString &text) : CommandExecutor(), mText(text)
    {
    }
    ~TypeTextCommandExecutor() override = default;

  public:
    void execute() override;

    QByteArray toByteArray() const override;
    void fromByteArray(const QByteArray &data) override;

    QString toString() override;

    const QString &text() const
    {
        return mText;
    }
    void setText(const QString &newText)
    {
        mText = newText;
    }

  private:
    /// Text to type when the command is executed
    QString mText;
};

} // namespace checo::command_executor
