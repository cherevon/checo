#include "checo/qt/toggle_window_command_executor.h"

#include <QObject>

#ifdef WIN32
#include <Windows.h>
#endif // WIN32

namespace checo::qt
{

ToggleWindowCommandExecutor::ToggleWindowCommandExecutor(const Direction direction)
    : CommandExecutor(),
      m_Direction(direction)
{
}

ToggleWindowCommandExecutor::~ToggleWindowCommandExecutor() = default;

ToggleWindowCommandExecutor::Direction ToggleWindowCommandExecutor::direction() const
{
    return m_Direction;
}

void ToggleWindowCommandExecutor::execute()
{
#ifdef WIN32
    if (!m_IsInitialized)
    {
        keybd_event(VK_MENU, 0, 0, 0);
        m_IsInitialized = true;
    }

    if (m_Direction == Previous)
    {
        keybd_event(VK_SHIFT, 0, 0, 0);
    }
    keybd_event(VK_TAB, 0, 0, 0);
    keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
    if (m_Direction == Previous)
    {
        keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
    }
#endif // WIN32
}

void ToggleWindowCommandExecutor::finishExecution()
{
    if (m_IsInitialized)
    {
        keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
        m_IsInitialized = false;
    }
}

QByteArray ToggleWindowCommandExecutor::toByteArray() const
{
    QByteArray result(reinterpret_cast<const char *>(&m_Direction), sizeof(m_Direction));
    return result;
}

void ToggleWindowCommandExecutor::fromByteArray(const QByteArray &data)
{
    m_Direction = *reinterpret_cast<const Direction *>(data.data());
}

QString ToggleWindowCommandExecutor::toString()
{
    if (m_Direction == Direction::Next)
    {
        return QObject::tr("Toggle Task Forward");
    }
    else
    {
        return QObject::tr("Toggle Task Backward");
    }
}

} // namespace checo::qt
