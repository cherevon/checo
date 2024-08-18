#include "checo/command_executor/toggle_window.h"

#include <QObject>

#ifdef WIN32
#include <Windows.h>
#endif // WIN32

namespace checo::command_executor
{

ToggleWindowCommandExecutor::ToggleWindowCommandExecutor(const Direction direction)
    : CommandExecutor(), mDirection(direction)
{
}

ToggleWindowCommandExecutor::Direction ToggleWindowCommandExecutor::direction() const
{
    return mDirection;
}

void ToggleWindowCommandExecutor::execute()
{
#ifdef WIN32
    if (!mInitialized)
    {
        keybd_event(VK_MENU, 0, 0, 0);
        mInitialized = true;
    }

    if (mDirection == Previous)
    {
        keybd_event(VK_SHIFT, 0, 0, 0);
    }
    keybd_event(VK_TAB, 0, 0, 0);
    keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
    if (mDirection == Previous)
    {
        keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
    }
#endif // WIN32
}

void ToggleWindowCommandExecutor::finishExecution()
{
    if (mInitialized)
    {
        keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
        mInitialized = false;
    }
}

QByteArray ToggleWindowCommandExecutor::toByteArray() const
{
    QByteArray result(reinterpret_cast<const char *>(&mDirection), sizeof(mDirection));
    return result;
}

void ToggleWindowCommandExecutor::fromByteArray(const QByteArray &data)
{
    mDirection = *reinterpret_cast<const Direction *>(data.data());
}

QString ToggleWindowCommandExecutor::toString()
{
    if (mDirection == Direction::Next)
    {
        return QObject::tr("Toggle Task Forward");
    }
    else
    {
        return QObject::tr("Toggle Task Backward");
    }
}

} // namespace checo::command_executor
