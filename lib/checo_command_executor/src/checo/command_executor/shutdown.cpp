#include "checo/command_executor/shutdown.h"

#include <QProcess>

namespace checo::command_executor
{

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

} // namespace checo::command_executor
