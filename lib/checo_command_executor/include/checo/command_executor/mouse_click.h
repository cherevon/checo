#pragma once

#include "checo/command_executor/command_executor.h"

namespace checo::command_executor
{

/// Command which executes mouse click event
class CHECO_COMMAND_EXECUTOR_EXPORT MouseClickCommandExecutor : public CommandExecutor
{
  public:
    MouseClickCommandExecutor() = default;
    explicit MouseClickCommandExecutor(const Qt::MouseButton button) : CommandExecutor(), mButton(button)
    {
    }
    ~MouseClickCommandExecutor() override = default;

  public:
    Qt::MouseButton button() const;

  public:
    void execute() override;

    QByteArray toByteArray() const override;
    void fromByteArray(const QByteArray &data) override;

    QString toString() override;

  private:
    Qt::MouseButton mButton{Qt::LeftButton};
};

} // namespace checo::command_executor
