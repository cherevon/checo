#pragma once

#include "checo/command_executor/command_executor.h"

namespace checo::command_executor
{

/// Command to shut PC down
class CHECO_COMMAND_EXECUTOR_EXPORT ShutdownCommandExecutor : public CommandExecutor
{
  public:
    ShutdownCommandExecutor() = default;
    ~ShutdownCommandExecutor() override = default;

  public:
    void execute() override;

    QByteArray toByteArray() const override;
    void fromByteArray(const QByteArray &data) override;

    QString toString() override;
};

} // namespace checo::command_executor
