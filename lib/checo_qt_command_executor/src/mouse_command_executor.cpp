#include "checo/qt/mouse_command_executor.h"

#ifdef WIN32
#include <Windows.h>
// WARNING: Windows.h MUST be included first
#include "WinUser.h"
#endif // WIN32

#include <QDataStream>

namespace checo::qt
{

MouseCommandExecutor::MouseCommandExecutor() = default;

MouseCommandExecutor::MouseCommandExecutor(const std::shared_ptr<QMouseEvent> &event)
    : CommandExecutor{},
      m_Event{event}
{
}

MouseCommandExecutor::~MouseCommandExecutor() = default;

std::shared_ptr<QMouseEvent> MouseCommandExecutor::event() const
{
    return m_Event;
}

void MouseCommandExecutor::execute()
{
#ifdef WIN32
    // Association of press/release events for all mouse buttons
    const std::map<Qt::MouseButton, std::pair<quint32, quint32>> actionMap = {
        {Qt::LeftButton, {MOUSEEVENTF_LEFTDOWN, MOUSEEVENTF_LEFTUP}},
        {Qt::RightButton, {MOUSEEVENTF_RIGHTDOWN, MOUSEEVENTF_RIGHTUP}},
        {Qt::MiddleButton, {MOUSEEVENTF_MIDDLEDOWN, MOUSEEVENTF_MIDDLEUP}},
        {Qt::XButton1, {MOUSEEVENTF_XDOWN, MOUSEEVENTF_XUP}}};

    DWORD dwData = 0;
    if (m_Event->button() == Qt::XButton1)
        dwData = XBUTTON1;
    if (m_Event->button() == Qt::XButton2)
        dwData = XBUTTON2;

    // Execute double click
    if (m_Event->type() == QEvent::MouseButtonDblClick)
    {
        for (unsigned char i = 0; i < 2; ++i)
        {
            mouse_event(actionMap.at(m_Event->button()).first, 0, 0, dwData, 0);
            mouse_event(actionMap.at(m_Event->button()).second, 0, 0, dwData, 0);
        }
        return;
    }

    // Execute mouse move
    if (m_Event->type() == QEvent::MouseMove)
    {
        mouse_event(MOUSEEVENTF_MOVE, m_Event->pos().x(), m_Event->pos().y(), 0, 0);
        return;
    }

    // Execute mouse press event
    if (m_Event->type() == QEvent::MouseButtonPress)
        mouse_event(actionMap.at(m_Event->button()).first, 0, 0, dwData, 0);

    // Execute mouse release event
    if (m_Event->type() == QEvent::MouseButtonRelease)
        mouse_event(actionMap.at(m_Event->button()).second, 0, 0, dwData, 0);
#endif // WIN32
}

QByteArray MouseCommandExecutor::toByteArray() const
{
    QByteArray result;

    QDataStream resultStream(&result, QIODevice::WriteOnly);
    resultStream << m_Event->type() << m_Event->button() << m_Event->localPos() << m_Event->globalPos();

    return result;
}

void MouseCommandExecutor::fromByteArray(const QByteArray &data)
{
    QEvent::Type eventType;
    Qt::MouseButton eventButton;
    QPointF localPos;
    QPoint globalPos;

    QDataStream dataStream(data);
    dataStream >> eventType >> eventButton >> localPos >> globalPos;

    m_Event = std::make_shared<QMouseEvent>(eventType, localPos, globalPos, eventButton, eventButton, Qt::NoModifier);
}

QString MouseCommandExecutor::toString()
{
    if (m_Event->type() == QEvent::MouseMove)
    {
        QString direction;
        const qreal dx = m_Event->position().x();
        const qreal dy = m_Event->position().y();

        if (dy < 0.0)
        {
            direction += QObject::tr("Up ");
        }
        else if (dy > 0.0)
        {
            direction += QObject::tr("Down ");
        }

        if (dx < 0.0)
        {
            direction += QObject::tr("Left ");
        }
        else if (dx > 0.0)
        {
            direction += QObject::tr("Right ");
        }

        return QObject::tr("Mouse Pointer ") + direction;
    }
    else
    {
        return QObject::tr("Mouse");
    }
}

} // namespace checo::qt
