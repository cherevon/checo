#pragma once

#include "checo/command_executor/command_executor.h"

namespace checo::command_executor
{

/// Command which executes mouse move event
class CHECO_COMMAND_EXECUTOR_EXPORT MouseMoveCommandExecutor : public CommandExecutor
{
  public:
    enum Direction
    {
        Left,
        Right,
        Up,
        Down
    };

  public:
    MouseMoveCommandExecutor() = default;
    explicit MouseMoveCommandExecutor(const Direction direction) : CommandExecutor(), mDirection(direction)
    {
    }
    ~MouseMoveCommandExecutor() override = default;

  public:
    Direction direction() const;

  public:
    void execute() override;

    QByteArray toByteArray() const override;
    void fromByteArray(const QByteArray &data) override;

    QString toString() override;

  private:
    Direction mDirection = Left;
};

} // namespace checo::command_executor
