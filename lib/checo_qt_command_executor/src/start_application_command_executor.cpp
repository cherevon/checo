#include "checo/qt/start_application_command_executor.h"

#include <QDesktopServices>
#include <QUrl>

namespace checo::qt
{

StartApplicationCommandExecutor::StartApplicationCommandExecutor() = default;

StartApplicationCommandExecutor::StartApplicationCommandExecutor(const QString &displayName,
    const QFileInfo &executable)
    : CommandExecutor(),
      m_DisplayName(displayName),
      m_Executable(executable)
{
}

StartApplicationCommandExecutor::~StartApplicationCommandExecutor() = default;

const QString &StartApplicationCommandExecutor::displayName() const
{
    return m_DisplayName;
}

const QFileInfo &StartApplicationCommandExecutor::executable() const
{
    return m_Executable;
}

void StartApplicationCommandExecutor::execute()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(m_Executable.absoluteFilePath()));
}

QByteArray StartApplicationCommandExecutor::toByteArray() const
{
    return m_DisplayName.toUtf8() + "|" + m_Executable.absoluteFilePath().toUtf8();
}

void StartApplicationCommandExecutor::fromByteArray(const QByteArray &data)
{
    const QList<QByteArray> parts = data.split('|');
    if (parts.size() == 2)
    {
        m_DisplayName = QString::fromUtf8(parts[0]);
        m_Executable = QFileInfo(QString::fromUtf8(parts[1]));
    }
}

QString StartApplicationCommandExecutor::toString()
{
    return QObject::tr("Launch \"%1\"").arg(m_DisplayName);
}

} // namespace checo::qt
