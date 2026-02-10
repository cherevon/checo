#include "checo/qt/complex_command_executor.h"

#include <QTimer>

namespace checo::qt
{

ComplexCommandExecutor::ComplexCommandExecutor() = default;

ComplexCommandExecutor::~ComplexCommandExecutor() = default;

void ComplexCommandExecutor::execute()
{
    uint32_t totalDelayTime = 1;
    for (auto &[delayTime, cmd] : m_Commands)
    {
        if (cmd == nullptr)
        {
            continue;
        }

        totalDelayTime += delayTime;
        QTimer::singleShot(totalDelayTime, [cmd] { cmd->execute(); });
    }
}

QByteArray ComplexCommandExecutor::toByteArray() const
{
    return QByteArray();
}

void ComplexCommandExecutor::fromByteArray(const QByteArray &)
{
    throw std::runtime_error("NOT SUPPORTED");
}

QString ComplexCommandExecutor::toString()
{
    return QObject::tr("Complex command");
}

const std::list<std::pair<uint32_t, std::shared_ptr<CommandExecutor>>> &ComplexCommandExecutor::commands() const
{
    return m_Commands;
}

void ComplexCommandExecutor::addCommand(const std::shared_ptr<CommandExecutor> &cmd, const uint32_t delayTime)
{
    m_Commands.push_back(std::make_pair(delayTime, cmd));
}

} // namespace checo::qt
