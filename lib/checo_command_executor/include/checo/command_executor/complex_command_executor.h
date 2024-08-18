#pragma once

#include "checo/command_executor/command_executor.h"

namespace checo::command_executor
{

/// Command which executes a sequence of subcommands when execute() is called
class CHECO_COMMAND_EXECUTOR_EXPORT ComplexCommandExecutor : public CommandExecutor
{
  public:
    ComplexCommandExecutor() = default;
    ~ComplexCommandExecutor() override = default;

  public:
    void execute() override;

  public:
    QByteArray toByteArray() const override;
    void fromByteArray(const QByteArray &) override;

    QString toString() override;

  public:
    const std::list<std::pair<uint32_t, std::shared_ptr<CommandExecutor>>> &commands() const;
    /** Add command in the end of execution sequence
     * @param cmd Command to be added
     * @param delayTime Time to wait before command execution (in milliseconds)
     */
    void addCommand(const std::shared_ptr<CommandExecutor> &cmd, const uint32_t delayTime = 0);

  public:
    /// Commands which are executed sequentially with delay time between them (in milliseconds)
    std::list<std::pair<uint32_t, std::shared_ptr<CommandExecutor>>> mCommands;
};

} // namespace checo::command_executor
