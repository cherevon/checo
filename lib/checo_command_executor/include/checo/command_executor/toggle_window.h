#pragma once

#include "checo/command_executor/command_executor.h"

namespace checo::command_executor
{

/// Toggle window (Alt+Tab) to the next or previous one
class CHECO_COMMAND_EXECUTOR_EXPORT ToggleWindowCommandExecutor : public CommandExecutor
{
  public:
    enum Direction
    {
        Next,
        Previous,
    };

  public:
    explicit ToggleWindowCommandExecutor(const Direction direction = Next);

  public:
    Direction direction() const;

  public:
    void execute() override;
    void finishExecution() override;

    QByteArray toByteArray() const override;
    void fromByteArray(const QByteArray &data) override;

    QString toString() override;

  private:
    bool mInitialized = false;
    Direction mDirection = Next;
};

} // namespace checo::command_executor
