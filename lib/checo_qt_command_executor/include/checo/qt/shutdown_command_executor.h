#pragma once

#include "checo/qt/command_executor.h"
#include "checo_qt_command_executor_export.h"

namespace checo::qt
{

/// Command to shut PC down
class CHECO_QT_COMMAND_EXECUTOR_EXPORT ShutdownCommandExecutor : public CommandExecutor
{
  public:
    ShutdownCommandExecutor();
    ~ShutdownCommandExecutor() override;

  public:
    void execute() override;

    QByteArray toByteArray() const override;
    void fromByteArray(const QByteArray &data) override;

    QString toString() override;
};

} // namespace checo::qt
