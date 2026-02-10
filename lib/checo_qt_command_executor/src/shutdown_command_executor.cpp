#include "checo/qt/shutdown_command_executor.h"

#include <QProcess>

namespace checo::qt
{

ShutdownCommandExecutor::ShutdownCommandExecutor() = default;

ShutdownCommandExecutor::~ShutdownCommandExecutor() = default;

void ShutdownCommandExecutor::execute()
{
    QProcess::startDetached("shutdown", {"/s", "/f", "/t", "0"});
}

QByteArray ShutdownCommandExecutor::toByteArray() const
{
    return QByteArray();
}

void ShutdownCommandExecutor::fromByteArray(const QByteArray &)
{
    // This command executor has no additional information that can be stored in QByteArray
}

QString ShutdownCommandExecutor::toString()
{
    return QObject::tr("Shutdown PC");
}

} // namespace checo::qt
