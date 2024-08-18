#include "checo/command_executor/mouse_click.h"

#include <QDataStream>
#include <QIODevice>

#include <map>

#ifdef WIN32
#include <Windows.h>
// WARNING: Windows.h MUST be included first
#include "WinUser.h"
#endif // WIN32

namespace checo::command_executor
{

Qt::MouseButton MouseClickCommandExecutor::button() const
{
    return mButton;
}

void MouseClickCommandExecutor::execute()
{
#ifdef WIN32
    // Association of press/release events for all mouse buttons
    const std::map<Qt::MouseButton, std::pair<quint32, quint32>> actionMap = {
        {Qt::LeftButton, {MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP}},
        {Qt::RightButton, {MOUSEEVENTF_RIGHTDOWN, MOUSEEVENTF_RIGHTUP}},
        {Qt::MiddleButton, {MOUSEEVENTF_MIDDLEDOWN, MOUSEEVENTF_MIDDLEUP}},
        {Qt::XButton1, {MOUSEEVENTF_XDOWN, MOUSEEVENTF_XUP}}};

    DWORD dwData = 0;
    if (mButton == Qt::XButton1)
        dwData = XBUTTON1;
    if (mButton == Qt::XButton2)
        dwData = XBUTTON2;

    // Execute mouse click
    mouse_event(actionMap.at(mButton).first, 0, 0, dwData, 0);
    mouse_event(actionMap.at(mButton).second, 0, 0, dwData, 0);
#endif // WIN32
}

QByteArray MouseClickCommandExecutor::toByteArray() const
{
    QByteArray result;

    QDataStream resultStream(&result, QIODevice::WriteOnly);
    resultStream << mButton;

    return result;
}

void MouseClickCommandExecutor::fromByteArray(const QByteArray &data)
{
    QDataStream dataStream(data);
    dataStream >> mButton;
}

QString MouseClickCommandExecutor::toString()
{
    switch (mButton)
    {
    case Qt::LeftButton:
        return QObject::tr("Mouse Left Click");
    case Qt::RightButton:
        return QObject::tr("Mouse Right Click");
    default:
        return QObject::tr("Mouse Click");
    }
}

} // namespace checo::command_executor
