#include "checo/command_executor/mouse_move.h"

#include <QApplication>
#include <QDataStream>
#include <QIODevice>
#include <QScreen>

#ifdef WIN32
#include <Windows.h>
// WARNING: Windows.h MUST be included first
#include <WinUser.h>
#endif // WIN32

namespace checo::command_executor
{

MouseMoveCommandExecutor::Direction MouseMoveCommandExecutor::direction() const
{
    return mDirection;
}

void MouseMoveCommandExecutor::execute()
{
    const QRect screenGeometry = qApp->screens().front()->geometry();
    const int horzMovement = max(static_cast<int>(screenGeometry.width() * 0.004f), 3);
    const int vertMovement = max(static_cast<int>(screenGeometry.height() * 0.004f), 3);

#ifdef WIN32
    switch (mDirection)
    {
    case Left:
        mouse_event(MOUSEEVENTF_MOVE, -horzMovement, 0, 0, 0);
        break;
    case Right:
        mouse_event(MOUSEEVENTF_MOVE, horzMovement, 0, 0, 0);
        break;
    case Up:
        mouse_event(MOUSEEVENTF_MOVE, 0, -vertMovement, 0, 0);
        break;
    case Down:
        mouse_event(MOUSEEVENTF_MOVE, 0, vertMovement, 0, 0);
        break;
    }
#endif // WIN32
}

QByteArray MouseMoveCommandExecutor::toByteArray() const
{
    QByteArray result;

    QDataStream resultStream(&result, QIODevice::WriteOnly);
    resultStream << mDirection;

    return result;
}

void MouseMoveCommandExecutor::fromByteArray(const QByteArray &data)
{
    QDataStream dataStream(data);
    dataStream >> mDirection;
}

QString MouseMoveCommandExecutor::toString()
{
    switch (mDirection)
    {
    case Left:
        return QObject::tr("Mouse Pointer Left");
    case Right:
        return QObject::tr("Mouse Pointer Right");
    case Up:
        return QObject::tr("Mouse Pointer Up");
    case Down:
        return QObject::tr("Mouse Pointer Down");
    default:
        return QObject::tr("Mouse Move");
    }
}

} // namespace checo::command_executor
