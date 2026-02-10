#include "checo/qt/mouse_click_command_executor.h"

#include <QDataStream>
#include <QIODevice>

#include <map>

#ifdef WIN32
#include <Windows.h>
// WARNING: Windows.h MUST be included first
#include "WinUser.h"
#endif // WIN32

namespace checo::qt
{

MouseClickCommandExecutor::MouseClickCommandExecutor() = default;

MouseClickCommandExecutor::MouseClickCommandExecutor(const Qt::MouseButton button)
    : CommandExecutor{},
      m_Button{button}
{
}

MouseClickCommandExecutor::~MouseClickCommandExecutor() = default;

Qt::MouseButton MouseClickCommandExecutor::button() const
{
    return m_Button;
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
    if (m_Button == Qt::XButton1)
        dwData = XBUTTON1;
    if (m_Button == Qt::XButton2)
        dwData = XBUTTON2;

    // Execute mouse click
    mouse_event(actionMap.at(m_Button).first, 0, 0, dwData, 0);
    mouse_event(actionMap.at(m_Button).second, 0, 0, dwData, 0);
#endif // WIN32
}

QByteArray MouseClickCommandExecutor::toByteArray() const
{
    QByteArray result;

    QDataStream resultStream(&result, QIODevice::WriteOnly);
    resultStream << m_Button;

    return result;
}

void MouseClickCommandExecutor::fromByteArray(const QByteArray &data)
{
    QDataStream dataStream(data);
    dataStream >> m_Button;
}

QString MouseClickCommandExecutor::toString()
{
    switch (m_Button)
    {
    case Qt::LeftButton:
        return QObject::tr("Mouse Left Click");
    case Qt::RightButton:
        return QObject::tr("Mouse Right Click");
    default:
        return QObject::tr("Mouse Click");
    }
}

} // namespace checo::qt
