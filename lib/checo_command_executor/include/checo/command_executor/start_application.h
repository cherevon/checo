#pragma once

#include "checo/command_executor/command_executor.h"
#include "checo/os/application_info.h"

namespace checo::command_executor
{

/// Command to launch application
class CHECO_COMMAND_EXECUTOR_EXPORT StartAppCommandExecutor : public CommandExecutor
{
  public:
    StartAppCommandExecutor() = default;
    explicit StartAppCommandExecutor(const checo::os::ApplicationInfo &appInfo);
    ~StartAppCommandExecutor() override = default;

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
