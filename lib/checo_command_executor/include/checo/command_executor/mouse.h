#pragma once

#include "checo/command_executor/command_executor.h"

#include <QMouseEvent>

#include <memory>

namespace checo::command_executor
{

/// Command which executes mouse event
class CHECO_COMMAND_EXECUTOR_EXPORT MouseCommandExecutor : public CommandExecutor
{
  public:
    MouseCommandExecutor() = default;
    explicit MouseCommandExecutor(const std::shared_ptr<QMouseEvent> &event) : CommandExecutor(), mEvent(event)
    {
    }
    ~MouseCommandExecutor() override = default;

  public:
    std::shared_ptr<QMouseEvent> event() const;

  public:
    void execute() override;

    QByteArray toByteArray() const override;
    void fromByteArray(const QByteArray &data) override;

    QString toString() override;

  private:
    /// Event which should be executed
    std::shared_ptr<QMouseEvent> mEvent = nullptr;
};

} // namespace checo::command_executor
