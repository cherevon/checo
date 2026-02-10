#pragma once

#include "checo_qt_command_executor_export.h"

#include <QByteArray>
#include <QString>

namespace checo::qt
{

/// Command which performs some operation when execute() is called
class CHECO_QT_COMMAND_EXECUTOR_EXPORT CommandExecutor
{
  public:
    CommandExecutor();
    virtual ~CommandExecutor();

  public:
    /// Execute the command
    virtual void execute() = 0;

    /** Finalize all side effects from command execution (if the command saves state between execute() calls
     * @remark For example, Alt+Tab command press Alt button in execute() but doesn't release it because Tab can be
     * pressed more than once
     */
    virtual void finishExecution();

    /// Save settings of the command to the binary data
    virtual QByteArray toByteArray() const = 0;
    /// Load settings of the command from the binary data
    virtual void fromByteArray(const QByteArray &data) = 0;

    virtual QString toString() = 0;
};

} // namespace checo::qt
