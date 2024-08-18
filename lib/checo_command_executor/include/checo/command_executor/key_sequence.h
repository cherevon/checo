#pragma once

#include "checo/command_executor/command_executor.h"

#include <QKeySequence>

#include <vector>

namespace checo::command_executor
{

/// Command which executes QKeySequence
class CHECO_COMMAND_EXECUTOR_EXPORT KeySequenceCommandExecutor : public CommandExecutor
{
  public:
    KeySequenceCommandExecutor() = default;
    explicit KeySequenceCommandExecutor(const std::vector<Qt::Key> &keys) : CommandExecutor(), mKeySequence(keys)
    {
    }
    ~KeySequenceCommandExecutor() override = default;

  public:
    void execute() override;

    QByteArray toByteArray() const override;
    void fromByteArray(const QByteArray &data) override;

    QString toString() override;

  public:
    const std::vector<Qt::Key> &keySequence() const;

  private:
    std::vector<Qt::Key> mKeySequence;
};

} // namespace checo::command_executor
