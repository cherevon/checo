#pragma once

#include "checo/qt/command_executor.h"
#include "checo_qt_command_executor_export.h"

#include <QFileInfo>
#include <QString>

namespace checo::qt
{

/// Command to terminate running application
class CHECO_QT_COMMAND_EXECUTOR_EXPORT TerminateApplicationCommandExecutor : public CommandExecutor
{
  public:
    TerminateApplicationCommandExecutor();
    TerminateApplicationCommandExecutor(const QString &displayName, const QFileInfo &executable);
    ~TerminateApplicationCommandExecutor() override;

  public:
    const QString &displayName() const;
    const QFileInfo &executable() const;

  public:
    void execute() override;

    QByteArray toByteArray() const override;
    void fromByteArray(const QByteArray &data) override;

    QString toString() override;

  private:
    QString m_DisplayName{};
    QFileInfo m_Executable{};
};

} // namespace checo::qt
