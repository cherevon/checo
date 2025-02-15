#include "checo/command_executor/mouse.h"

#ifdef WIN32
#include <Windows.h>
// WARNING: Windows.h MUST be included first
#include "WinUser.h"
#endif // WIN32

#include <QDataStream>

namespace checo::command_executor
{

std::shared_ptr<QMouseEvent> MouseCommandExecutor::event() const
{
    return mEvent;
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
    if (mEvent->button() == Qt::XButton1)
        dwData = XBUTTON1;
    if (mEvent->button() == Qt::XButton2)
        dwData = XBUTTON2;

    // Execute double click
    if (mEvent->type() == QEvent::MouseButtonDblClick)
    {
        for (unsigned char i = 0; i < 2; ++i)
        {
            mouse_event(actionMap.at(mEvent->button()).first, 0, 0, dwData, 0);
            mouse_event(actionMap.at(mEvent->button()).second, 0, 0, dwData, 0);
        }
        return;
    }

    // Execute mouse move
    if (mEvent->type() == QEvent::MouseMove)
    {
        mouse_event(MOUSEEVENTF_MOVE, mEvent->pos().x(), mEvent->pos().y(), 0, 0);
        return;
    }

    // Execute mouse press event
    if (mEvent->type() == QEvent::MouseButtonPress)
        mouse_event(actionMap.at(mEvent->button()).first, 0, 0, dwData, 0);

    // Execute mouse release event
    if (mEvent->type() == QEvent::MouseButtonRelease)
        mouse_event(actionMap.at(mEvent->button()).second, 0, 0, dwData, 0);
#endif // WIN32
}

QByteArray MouseCommandExecutor::toByteArray() const
{
    QByteArray result;

    QDataStream resultStream(&result, QIODevice::WriteOnly);
    resultStream << mEvent->type() << mEvent->button() << mEvent->localPos() << mEvent->globalPos();

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

    mEvent = std::make_shared<QMouseEvent>(eventType, localPos, globalPos, eventButton, eventButton, Qt::NoModifier);
}

QString MouseCommandExecutor::toString()
{
    if (mEvent->type() == QEvent::MouseMove)
    {
        QString direction;
        const qreal dx = mEvent->position().x();
        const qreal dy = mEvent->position().y();

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

} // namespace checo::command_executor
