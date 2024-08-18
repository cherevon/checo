#pragma once

#include "checo/command_executor/command_executor.h"
#include "checo/os/application_info.h"

namespace checo::command_executor
{

/// Command to terminate running application
class CHECO_COMMAND_EXECUTOR_EXPORT TerminateAppCommandExecutor : public CommandExecutor
{
  public:
    TerminateAppCommandExecutor() = default;
    TerminateAppCommandExecutor(const checo::os::ApplicationInfo &appInfo);
    ~TerminateAppCommandExecutor() override = default;

  public:
    const checo::os::ApplicationInfo &applicationInfo() const;

  public:
    void execute() override;

    QByteArray toByteArray() const override;
    void fromByteArray(const QByteArray &data) override;

    QString toString() override;

  private:
    checo::os::ApplicationInfo mAppInfo;
};

} // namespace checo::command_executor
